#include <math.h>
#include "h1_electricpot.h"
#include "../integrate_romberg/integrate_romberg.h"
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