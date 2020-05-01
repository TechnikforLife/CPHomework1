#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../generalmemorymanager/generalmemorymanager.h"
#include "../integrate_romberg/integrate_romberg.h"
#include "../h1_electricpot/h1_electricpot.h"


void value_table(double zstart,double zend,double astart,char* filename,
				 double (*fp)(double*)){
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

double symfirstderivative(double h,double (*fp)(double*),
						  double* variables){
	double current,prev;
	double relprec=1e-8;
	double z=variables[1];
	
	variables[1]=z+h;
	current=fp(variables);
	variables[1]=z-h;
	current=(current-fp(variables))/(2.*h);
	do{
		h/=2.;
		prev=current;
		
		variables[1]=z+h;
		current=fp(variables);
		variables[1]=z-h;
		current=(current-fp(variables))/(2.*h);
	}while(fabs (current-prev)>fabs((current+prev)*relprec/2.));
	return current;
}

double e_field_part2(double* variables){

	return -symfirstderivative (1e-1, solveintegral_part1, variables);
}

double diffintegrant(double* variables)
{
  /**
	 * Declarations:
	 * variables[0]=x
	 * variables[1]=z
	 * variables[2]=a
	 */
  return exp(-pow(variables[0]/variables[2],2))/pow(pow(variables[0],2)+
													pow(variables[1],2), 1.5);
}

double solveH22(double*variables){

	/**
	 * Declarations:
	 * prefix			Prefix of the integral
	 * prec				Precision to be used
	 * upperboundary	Start value of the upperboundary
	 * n_0				Start value of the amount of subintervalls
	 */
	double prefix=variables[1]*2./(sqrt (M_PI)*variables[2]);
	double prec=1e-8;
	double upperboundary_sv=1.;
	int n_0=2;

	return prefix*romberg_converge_check(variables,0.,
									upperboundary_sv,diffintegrant,prec,n_0,1);
}

double potentialH3(double *variables)
{
	double v1, v2;
	double d = 12;
	double z = variables[1];
	double a1 = 4;
	double a2 = variables[3];
	if (a2 < a1/10||a2 > a1)
		{
			printf("Parameter a2 out of Range, forcing it to be a1!");
			variables[3] = a1;
		}
	variables[1] = z - d;
	v2 = solveintegral_part1(variables);
	variables[1] = z;
	variables[3] = a1;
	v1 = solveintegral_part1(variables);
	variables[3] = a2;
	return v1+v2;
}

double electricfiledsH3(double *variables)
{
	return -symfirstderivative(1e-1,potentialH3, variables);
}

double rootsecant(double a,double b,double (*fp)(double*),double precision, double *variables){
	/**
	 * Declarations:
	 * 
	 * @var x_i 	Current x
	 * @var x_im1	Prev x
	 * @var x_ip1	Next x
	 * @var i		Itteration variable
	 * 
	 */
	double x_i=a;
	double x_im1=b;
	double x_ip1=b+1;
	int i;
	
	/**
	 * @note	Try to estimate the root of "fp" with the given startvalues
	 * 			and to the given precision.
	 */
	for(i=0;i<10000;i++){
		
		x_ip1=x_i+(fp(x_i)*(x_im1-x_i))/(fp(x_i)-fp(x_im1));
		if(fabs(x_ip1-x_i)<precision){
			break;
		}
		x_im1=x_i;
		x_i=x_ip1;
	}
	if(i==10000){
		printf("[WARNING] Could not reach given precision!\n");
	}
	return x_ip1;
}



int main (int argc,char *argv[]){
	
	
	mem_init (0);
	value_table(1e-2,10.,1e-3,"data/number1.dat",solveintegral_part1);
	
	value_table (1e-2, 10., 1e-1, "data/number2.dat", e_field_part2);
	
	value_table (1e-2, 10., 1e-1, "data/number22.dat", solveH22);
	double variables[3] = {1, 2, 3};	
	printf("The electric field at the given location is %lf and the potential is %lf\n", electricfiledsH3(variables), potentialH3(variables));
	mem_free_all ();
	return EXIT_SUCCESS;
}
