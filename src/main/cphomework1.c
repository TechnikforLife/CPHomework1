#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../generalmemorymanager/generalmemorymanager.h"
#include "../integrate_romberg/integrate_romberg.h"
#include <gsl/gsl_const_mksa.h>

double f_i_integral1(double * variables){
	
	/**
	 * Declarations:
	 * variables[0]=x
	 * variables[1]=z
	 * variables[2]=a
	 */
	return exp(-pow(variables[0],2)/(pow(variables[2],2)))
			/sqrt (pow(variables[0],2)+pow(variables[1],2));
}
double solveintegral_part1(double*variables){
	
	/**
	 * Declarations:
	 * prefix			Prefix of the integral
	 * prec				Precision to be used
	 * upperboundary	Start value of the upperboundary
	 * n_0				Start value of the amount of subintervalls
	 */
	double prefix=2./(sqrt (M_PI)*variables[2]);
	double prec=1e-8;
	double upperboundary_sv=1.;
	int n_0=2;
	
	return prefix*romberg_converge_check(variables,0.,
									upperboundary_sv,f_i_integral1,prec,n_0,1);
}

void value_table(double zstart,double zend,double astart,char* filename,
				 double (*integrate_fp)(double*)){
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
	double amult=10;
	double zincrement=1e-1;
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
		current=integrate_fp(variables);
		fprintf(datafile,"%e;%e;",variables[1],current);
		variables[2]*=amult;
		
		/**
		 * @note	
		 * 
		 */
		do{
			current=integrate_fp(variables);
			fprintf(datafile,"%e;",current);
			variables[2]*=amult;
			
		}while(variables[2]<aend);
		variables[2]=aend;
		current=integrate_fp(variables);
		fprintf(datafile,"%e\n",current);
		
		variables[1]+=zincrement;
		
	}while(variables[1]<zend);
	
	fprintf (datafile,"\n");
	
	
	fclose (datafile);
}


int main (int argc,char *argv[]){
	
	
	mem_init (0);
	//double variables[]={0.,0.1,1000.};
	//printf("%.10e\n",solveintegral_part1 (variables));
	value_table(1e-2,10.,1e-3,"data/number1.dat",solveintegral_part1);
	
	
	mem_free_all ();
	return EXIT_SUCCESS;
}
