#include <math.h>
#include "h2_electricfield.h"
#include <stdio.h>
#include "../integrate_romberg/integrate_romberg.h"
#include "../h1_electricpot/h1_electricpot.h"

double symfirstderivative(double h,double (*fp)(double*),
						  double* variables){
	double current,prev;
	double relprec=1e-8;
	double z=variables[1];
	int i=0;
	if(fabs(variables[1])<1){
		h=variables[1]/10.;
	}
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
		i++;
		if(i>1000){
			printf("[WARNING] To many itterations in symfirstderivative\n");
			break;
		}
	}while(fabs (current-prev)>fabs((current+prev)*relprec/2.));
	variables[1]=z;
	return current;
}

double e_field_part2(double* variables){
	/**
	 * Declarations:
	 * variables[0]=x
	 * variables[1]=z
	 * variables[2]=a
	 */
	return -symfirstderivative (1e-1, solveintegral_part1, variables);
}

double diffintegrantH2_2(double* variables){
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
								upperboundary_sv,diffintegrantH2_2,prec,n_0,1);
}
