#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../h1_electricpot/h1_electricpot.h"
#include "../h2_electricfield/h2_electricfield.h"
double potentialH3(double *variables){
	double v1, v2;
	double d = 12;
	double z = variables[1];
	double a1 = 4;
	double a2 = variables[3];
	if (a2 < a1/10.||a2 > a1)
		{
			printf("Parameter a2=%e out of Range, forcing it to be a1!\n",a2);
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

double electricfieldsH3(double *variables){
	return -symfirstderivative(1e-1,potentialH3, variables);
}

double rootsecant(double a,double b,double (*fp)(double*),double precision, 
				  double *variables){
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
		
		//x_ip1=x_i+(fp(x_i)*(x_im1-x_i))/(fp(x_i)-fp(x_im1));
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
