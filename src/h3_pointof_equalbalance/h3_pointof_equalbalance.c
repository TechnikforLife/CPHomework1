#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../h1_electricpot/h1_electricpot.h"
#include "../h2_electricfield/h2_electricfield.h"
double potentialH3(double *variables){
	/**
	 * Declarations:
	 * variables[0]=x
	 * variables[1]=z
	 * variables[2]=a_2
	 */
	double v1, v2;
	double d = 12;
	double z = variables[1];
	double a1 = 4;
	double a2 = variables[2];
	if (a2 < a1/10.||a2 > a1){
		printf("Parameter a2=%e out of Range, forcing it to be a1!\n",a2);
		variables[2] = a1;
	}
	variables[1] = z - d;
	v2 = solveintegral_part1(variables);
	variables[1] = z;
	variables[2] = a1;
	//printf("xyz:%e,%e,%e\n",variables[0],variables[1],variables[2]);
	v1 = solveintegral_part1(variables);
	variables[2] = a2;
	return v1+4*v2;
}

double electricfieldsH3(double *variables){
	return -symfirstderivative(1e-1,potentialH3, variables);
}

double rootsecant(double a,double b,double (*fp)(double*),double relprecision, 
				  double *variables){
	/**
	 * Declarations:
	 * 
	 * @var z_i 	Current z
	 * @var z_im1	Prev z
	 * @var z_ip1	Next z
	 * @var i		Itteration variable
	 * 
	 */
	double z_i=a;
	double z_im1=b;
	double z_ip1=b+1;
	double temp;
	int i;
	
	/**
	 * @note	Try to estimate the root of "fp" with the given startvalues
	 * 			and to the given precision.
	 */
	for(i=0;i<10000;i++){
		//printf("a z_i=%e\tz_im1=%e\tz_ip1=%e\n",z_i,z_im1,z_ip1);
		variables[1]=z_i;
		temp=fp(variables);
		variables[1]=z_im1;
		//printf("b z_i=%e\tz_im1=%e\tz_ip1=%e\n",z_i,z_im1,z_ip1);
		z_ip1=z_i+(temp*(z_im1-z_i))/(temp-fp(variables));
		//printf("c z_i=%e\tz_im1=%e\tz_ip1=%e\n",z_i,z_im1,z_ip1);
		if(fabs(z_ip1-z_i)<fabs(relprecision*(z_ip1+z_i)/2.)){
			break;
		}
		z_im1=z_i;
		z_i=z_ip1;
	}
	if(i==10000){
		printf("[WARNING] Could not reach given precision in rootsecant!\n");
	}
	return z_ip1;
}
