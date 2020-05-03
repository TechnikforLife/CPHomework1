#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../generalmemorymanager/generalmemorymanager.h"
#include "../integrate_romberg/integrate_romberg.h"
#include "../h1_electricpot/h1_electricpot.h"
#include "../h2_electricfield/h2_electricfield.h"
#include "../h3_pointof_equalbalance/h3_pointof_equalbalance.h"

void value_table(double zstart,double zend,double zfactor,double astart,
				 double afactor,char* filename,double (*fp)(double*)){
	/**
	 * Declarations:
	 * variables		Saves the variables for function "f_i_integral1"
	 * variables[0]=x
	 * variables[1]=z
	 * variables[2]=a
	 * current			Saves the current value of the integral of "fp"
	 * aend				End value for a
	 * amult			Value to multiply a by
	 * zincrement		Value to increment z by
	 * datafile			Filestream to save the valuetable to
	 */
	double variables[3];
	double current=0.;
	double aend=4.;
	double amult=afactor;
	double zincrement=zfactor;
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
	 * @note	Save which values of a get used
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
		 * @note	Reset a and save the currently used z value as well as 
		 * 			the integral of the currently used z and "astart"
		 */
		variables[2]=astart;
		current=fp(variables);
		fprintf(datafile,"%e;%e;",variables[1],current);
		variables[2]*=amult;
		
		/**
		 * @note	
		 * 
		 */
		do{
			current=fp(variables);
			fprintf(datafile,"%e;",current);
			variables[2]*=amult;
			
		}while(variables[2]<aend);
		variables[2]=aend;
		current=fp(variables);
		fprintf(datafile,"%e\n",current);
		
		variables[1]+=zincrement;
	}while(variables[1]<zend);
	
	fprintf (datafile,"\n");
	
	
	fclose (datafile);
}


int main (int argc,char *argv[]){
	
	
	mem_init (0);
	value_table(/*zstart*/	1e-2,
				/*zend*/	10.,
				/*zfactor*/	0.1,
				/*astart*/	1e-3,
				/*afactor*/	10.,
				/*filename*/"data/number1.dat",
				/*fct*/		solveintegral_part1);
	
	value_table(/*zstart*/	1e-2,
				/*zend*/	10.,
				/*zfactor*/	0.1,
				/*astart*/	1e-1,
				/*afactor*/	10.,
				/*filename*/"data/number21.dat",
				/*fct*/		e_field_part2);
	
	value_table(/*zstart*/	1e-2,
				/*zend*/	10.,
				/*zfactor*/	0.1,
				/*astart*/	1e-1,
				/*afactor*/	10.,
				/*filename*/"data/number22.dat",
				/*fct*/		solveH22);
	
	/**
	 * Declarations:
	 * variables[0]=x
	 * variables[1]=z
	 * variables[2]=a
	 */
	
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
	
	double variables[3] = {1, 2, 2};
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
	
	mem_free_all ();
	return EXIT_SUCCESS;
}

