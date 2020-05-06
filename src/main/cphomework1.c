// Die folgenden Befehle müssen im Verzeichnis, 
// in dem die "Makefile" liegt ausgeführt werden:
// make
// make calc
// Nico Dichter, Florian Giefer
// Die Plots können mit "make plot" erstellt werden.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../generalmemorymanager/generalmemorymanager.h"
#include "../integrate_romberg/integrate_romberg.h"
#include "../h1_electricpot/h1_electricpot.h"
#include "../h2_electricfield/h2_electricfield.h"
#include "../h3_pointof_equalbalance/h3_pointof_equalbalance.h"

/** @fn void value_table(double zstart,double zend,double zincrement,
 * 			   double astart,double amult,char* filename,double (*fp)(double*));
 * @brief Calculates a value table for the given range of a and z
 * 
 * Calculates a value table with the first row being the used "a"'s 
 * in the calculation and the first column being the used "z"'s 
 * in the calculation.
 * In each step "z" gets increment by a constant value, 
 * while "a" gets multiplied by a constant value.
 * 
 * @param zstart		Start value for z (variable[1])
 * @param zend			End value for z (variable[1])
 * @param zincrement	Value to increment z by
 * @param astart		Start value for a (variables[2])
 * @param amult			Value to multiply a by (variables[2])
 * @param filename		File to save the value table to
 * @param fp			Function of which a value table should be created
 */

void value_table(double zstart,double zend,double zincrement,double astart,
				 double amult,char* filename,double (*fp)(double*)){
	/**
	 * Declarations:
	 * 
	 * variables		Saves the variables to be passed onto the use integrant
	 * variables[0]=x
	 * variables[1]=z
	 * variables[2]=a
	 * current			Saves the current value of "fp" with current 
	 * 						set of "variables"
	 * aend				End value for a
	 * datafile			Filestream to save the valuetable to
	 */
	double variables[3];
	double current=0.;
	double aend=4.;
	FILE* datafile=NULL;
	
	/**
	 * @note	Initialization of datafile and variables
	 */
	datafile=fopen(filename,"w");
	if(datafile==NULL){
		mem_free_all ();
		exit(EXIT_FAILURE);
	}
	variables[1]=zstart;
	variables[2]=astart;
	
	/**
	 * @note	Save which values of "a" get used
	 */
	fprintf(datafile,"0;%e;",variables[2]);
	variables[2]*=amult;
	do{
		fprintf(datafile,"%e;",variables[2]);
		variables[2]*=amult;
	}while(variables[2]<aend);
	variables[2]=aend;
	fprintf(datafile,"%e\n",variables[2]);
	
	do{
		/**
		 * @note	Reset "a" and save the currently used "z" value as well as 
		 * 			"fp" of the currently used "z" and "astart"
		 */
		variables[2]=astart;
		current=fp(variables);
		fprintf(datafile,"%e;%e;",variables[1],current);
		variables[2]*=amult;
		
		/**
		 * @note	Step trough each value of "a", until "aend" is reached,
		 * 			(multiplied by amult in each step) and save 
		 * 			"fp" of "z" and "a" in each step.
		 */
		do{
			current=fp(variables);
			fprintf(datafile,"%e;",current);
			variables[2]*=amult;
			
		}while(variables[2]<aend);
		
		/**
		 * @note	The value of "fp" at "z","aend" gets saved 
		 * 			in the last column and "z" gets incremented 
		 * 			for the next itteration step in "z".
		 * 			The itteration stops when "zend" is reached
		 */
		variables[2]=aend;
		current=fp(variables);
		fprintf(datafile,"%e\n",current);
		
		variables[1]+=zincrement;
	}while(variables[1]<zend);
	
	/**
	 * @note	Add an empty line to mark the end of the file and cleanup
	 */
	fprintf (datafile,"\n");
	fclose (datafile);
}


int main (void){
	/**
	 * Declarations:
	 * @var variables	Array with (used in H3.2):
	 * 						variables[0]=x
	 * 						variables[1]=z
	 * 						variables[2]=a_2
	 * @note	Intialization of the memory manager
	 */
	double variables[3] = {1, 2, 2};
	mem_init (0);
	
	/**
	 * @note	Use "value_table" to calculate a value table for each subtask, 
	 * 			using the corresponding functions of the corresponding moduls.
	 */
	//Part 1:
	value_table(/*zstart*/	1e-2,
				/*zend*/	10.,
				/*zfactor*/	0.1,
				/*astart*/	1e-3,
				/*afactor*/	10.,
				/*filename*/"data/number1.dat",
				/*fct*/		solveintegral_H12);
	
	//Part 2:
	value_table(/*zstart*/	1e-2,
				/*zend*/	10.,
				/*zfactor*/	0.1,
				/*astart*/	1e-1,
				/*afactor*/	10.,
				/*filename*/"data/number21.dat",
				/*fct*/		e_field_H21);
	
	value_table(/*zstart*/	1e-2,
				/*zend*/	10.,
				/*zfactor*/	0.1,
				/*astart*/	1e-1,
				/*afactor*/	10.,
				/*filename*/"data/number22.dat",
				/*fct*/		solveintegral_H22);
	
	//Part 3:
	value_table(/*zstart*/	1e-2,
				/*zend*/	11.,
				/*zfactor*/	0.1,
				/*astart*/	5e-1,
				/*afactor*/	2.,
				/*filename*/"data/number31.dat",
				/*fct*/		potentialH3);
	
	value_table(/*zstart*/	1e-1,
				/*zend*/	11.,
				/*zfactor*/	0.1,
				/*astart*/	5e-1,
				/*afactor*/	2.,
				/*filename*/"data/number32.dat",
				/*fct*/		electricfieldsH3);
	
	/**
	 * @note	The value table for H3.2 gets calculated (start a_2=6e-1)
	 * 			and saved in "data/number33.dat" for different values of a_2.
	 * 				(a_2 gets multiplied by 1.1 in each step until a_2>4 
	 * 				 and a_2=4 gets printed as the last value pair)
	 * 			("value_table" is not suitable for this, since z does not get 
	 * 				set to a specific value, it gets determinted)
	 */
	
	variables[2]=6e-1;
	FILE* zeros=fopen ("data/number33.dat", "w");
	do{
		
		fprintf(zeros,"%e;%e\n",variables[2],
			   rootsecant (1, 5, electricfieldsH3, 1e-8, variables));
		
		variables[2]*=1.1;
	}while(variables[2]<4.);
	
	variables[2]=4.;
	fprintf(zeros,"%e;%e\n",variables[2],
			   rootsecant (1, 5, electricfieldsH3, 1e-8, variables));
	
	
	/**
	 * @note	Cleanup
	 */
	fclose (zeros);
	mem_free_all ();
	return EXIT_SUCCESS;
}

