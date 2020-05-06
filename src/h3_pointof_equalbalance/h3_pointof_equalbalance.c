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
	 * @var v1,v2	Potential of each wire seperatly
	 * @var d		Distance between the wires
	 * @var z		Location at which the potential should be calculated
	 * @var a1		Paramter "a" for the first wire
	 * @var a2		Paramter "a" for the second wire
	 * 				Since only a2 should be varied, variables[2] corresponds 
	 * 				to a2 in this calculation.
	 */
	double v1, v2;
	double d = 12;
	double z = variables[1];
	double a1 = 4;
	double a2 = variables[2];
	/**
	 * @note	Check rather a2 is in the correct region
	 * 			Calculate each integral seperatly using "solveintegral_part1"
	 * 			from h1_electricpot.c and add them together at the end 
	 * 			with the correct weights (Q_1 and Q_2)
	 */
	if (a2 < a1/10.||a2 > a1){
		printf("Parameter a2=%e out of Range, forcing it to be a1!\n",a2);
		variables[2] = a1;
	}
	
	variables[1] = z - d;
	v2 = solveintegral_H12(variables);
	
	variables[1] = z;
	variables[2] = a1;
	v1 = solveintegral_H12(variables);
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
	 * 			and to the given precision using the secant method. 
	 * 			If the precision could not be reached in  10000 steps, 
	 * 			a Warning is been printed and the itteration stops
	 */
	for(i=0;i<10000;i++){
		
		variables[1]=z_i;
		temp=fp(variables);
		variables[1]=z_im1;
		
		z_ip1=z_i+(temp*(z_im1-z_i))/(temp-fp(variables));
		
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
