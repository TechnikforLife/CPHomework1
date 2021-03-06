// Die folgenden Befehle müssen im Verzeichnis, 
// in dem die "Makefile" liegt ausgeführt werden:
// make
// make calc
// Nico Dichter, Florian Giefer
// Die Plots können mit "make plot" erstellt werden.
#include <math.h>
#include "h2_electricfield.h"
#include <stdio.h>
#include "../integrate_romberg/integrate_romberg.h"
#include "../h1_electricpot/h1_electricpot.h"

double symfirstderivative(double h,double (*fp)(double*),
						  double* variables){
	/**
	 * Declarations:
	 * @var current		Current value of the derivative
	 * @var prev		Previous value of the derivative
	 * @var relprec		Relativ precision to be used for the calculation
	 * @var i			Itteration variable
	 */
	double current,prev;
	double relprec=1e-8;
	double z=variables[1];
	int i=0;
	
	/**
	 * @note	Prevent function call at variables[1]=0
	 * 			In each Itteration step:
	 * 				Halfen the stepsize h.
	 * 				Calculate fp(z+h) and fp(z-h)
	 * 				Estimate the value of the derivative at fp(z) until 
	 * 				the relative precision is met, 
	 * 				or an itteration limit is reached
	 */
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

double e_field_H21(double* variables){
	/**
	 * Declarations:
	 * variables[0]=x
	 * variables[1]=z
	 * variables[2]=a
	 */
	return -symfirstderivative (1e-1, solveintegral_H12, variables);
}

double integrant_H22(double* variables){
	/**
	 * Declarations:
	 * variables[0]=x
	 * variables[1]=z
	 * variables[2]=a
	 */
  return exp(-pow(variables[0]/variables[2],2))/pow(pow(variables[0],2)+
													pow(variables[1],2), 1.5);
}

double solveintegral_H22(double*variables){
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
								upperboundary_sv,integrant_H22,prec,n_0,1);
}
