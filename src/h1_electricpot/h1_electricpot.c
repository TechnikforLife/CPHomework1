#include <math.h>
#include "h1_electricpot.h"
#include "../integrate_romberg/integrate_romberg.h"
double integrant_H12(double * variables){
	
	/**
	 * Declarations:
	 * variables[0]=x
	 * variables[1]=z
	 * variables[2]=a
	 */
	return exp(-variables[0]*variables[0]/(variables[2]*variables[2]))
			/sqrt (variables[0]*variables[0]+variables[1]*variables[1]);
}

double solveintegral_H12(double*variables){
	
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
									upperboundary_sv,integrant_H12,prec,n_0,1);
}