// Die folgenden Befehle müssen im Verzeichnis, 
// in dem die "Makefile" liegt ausgeführt werden:
// make
// make calc
// Nico Dichter, Florian Giefer
// Die Plots können mit "make plot" erstellt werden.
#include <math.h>
#include "integrate_romberg.h"
#include <stdio.h>
#include <stdlib.h>
#include "../generalmemorymanager/generalmemorymanager.h"


double integratetrapez_posinf(double lowerboundary,
					   double (*fp)(double*),double subintervalllength,
					   double* variables,double relprecision){
	/**
	 * Declarations:
	 * 
	 * @var i		itteration variable
	 * @var sum		value of the sum
	 * @var f_x_i	f(x_i)
	 */
	
	int i=1;
	double sum=0.0;
	double f_x_i=0.0;
	
	/**
	 * @note	Calculate f(x_0) and add it to the sum with weight 0.5
	 */
	variables[0]=lowerboundary;
	sum=(*fp)(variables)/2.;
	
	/**
	 * @note	f(x_i) gets calulated and added to the sum,
	 * 			until the f(x_i)<sum*relprecision.
	 */
	do{
		variables[0]=lowerboundary+subintervalllength*i;
		f_x_i=(*fp)(variables);
		sum+=f_x_i;
		i++;
		if(i>1000000)break;
	//printf("%e,%e,i=%d\n",f_x_i,sum,i);
	}while((fabs(f_x_i)>fabs(relprecision)||(fabs(f_x_i)>fabs(sum*relprecision))));
	//printf ("-\n");
	/**
	 * @note	Calculate f(x_n) (n last relevant index)
	 * 			and add it to the sum with weight 0.5
	 */
	variables[0]=lowerboundary+(i+1)*subintervalllength;
	sum+=(*fp)(variables)/2.;
	return sum*subintervalllength;
}

int idxc(int i,int k, int* m_max_ptr){
	/**
	 * @note	*m_max_ptr*k	Contains the information about the stage
	 * 			+i				Index in current stage
	 * 			-k*(k-1)/2		Correction, because each stage is 1 step smaller
	 */
	return *m_max_ptr*k+i-k*(k-1)/2;
}

double integrate_romberg(double start,double end,double (*fp)(double*),
					   double* variables,int m_max,int n_0,double relprecision,
						 int* stagesused,int endisinf){
	/**
	 * Declarations:
	 * @var i,k		itteration variables
	 * @var t_tilde	Array of T_tild_ik's
	 * @var h		Array of h's
	 * @var n		Amount of subintervalls
	 * @var ret		Value to be returned by this function
	 */
	int i=0;
	int k=0;
	double* t_tilde;
	double* h;
	int n;
	double ret;
	
	/**
	 * @note	Memory allocation and setting of initial values
	 */
	t_tilde=(double*)mem_alloc (sizeof (double)*(m_max+1)*(m_max+2)/2);
	
	h=(double*)mem_alloc (sizeof (double)*(m_max+1));
	n=n_0;
	h[0]=(end-start)/(double)n;
	
	t_tilde[0]=integratetrapez_posinf (start, fp,
								h[0],variables, relprecision/100);
	
	for(i=1;i<=m_max;i++){
		/**
		 * @note	Calculate h_i and T_tilde_{i,0} using trapez integration
		 */
		h[i]=h[i-1]/2;
		t_tilde[idxc (i, 0, &m_max)]=integratetrapez_posinf (start, fp,
								h[i],variables, relprecision/100);
		
		/**
		 * @note	Calculate the T_tilde_{i,k} 
		 * 			for i in [1,k] using the recursionformula.
		 * 			If the needed relativ precision is met 
		 * 			the outer itteration is stopped.
		 */
		for(k=1;k<=i;k++){
			t_tilde[idxc (i, k, &m_max)]=-h[i-k]*h[i-k]/
					(h[i]*h[i]-h[i-k]*h[i-k])*t_tilde[idxc(i,k-1,&m_max)]
					+h[i]*h[i]/
					(h[i]*h[i]-h[i-k]*h[i-k])*t_tilde[idxc(i-1,k-1,&m_max)];
			
		}
		
		if(fabs(t_tilde[idxc(i,i,&m_max)]-t_tilde[idxc(i-1,i-1,&m_max)])
		   <fabs(relprecision*(t_tilde[idxc(i,i,&m_max)]+
							   t_tilde[idxc(i-1,i-1,&m_max)])/2))break;
	}
	
	/**
	 * @note	Save how many stages were used.
	 * 			Check rather the precision was reached.
	 */
	*stagesused=i;
	if(i>m_max){
		printf ("Relativ precision could not be reached in %d stages.\n",m_max);
		ret=t_tilde[idxc (m_max, m_max, &m_max)];
	}else{
		ret=t_tilde[idxc (i, i, &m_max)];
	}
	
	mem_free(h);
	mem_free(t_tilde);
	
	return ret;
}

double romberg_converge_check(double * variables,double lowerboundary,
						double upperboundary,double(*fp)(double*),
						double relprecision,int n_0,int endisinf){
	/**
	 * Declarations:
	 * @var current		current value of the integral
	 * @var m_max		Maximum amount of stages used in "integrate_romberg"
	 * @var stagesused	Saves how many stages were used in "integrate_romberg"
	 */
	double current;
	int m_max=30;
	int stagesused=0;
	
	/**
	 * @note	Calculate the value of the integral using "integrate_romberg"
	 * 			with increasing "m_max" until the precision is met 
	 * 			(stagesused<=m_max) or m_max>1000 (itteration limit).
	 */
	current=integrate_romberg (lowerboundary,upperboundary,fp,variables,m_max, 
							   n_0, relprecision,&stagesused,endisinf);
	while(stagesused>m_max){
		m_max*=2;
		current=integrate_romberg (lowerboundary,upperboundary,fp,variables,m_max, 
							   n_0, relprecision,&stagesused,endisinf);
		if(m_max>1000){
			printf("[WARNING] To many itterations in romberg_converge_check\n");
			break;
		}
	}
	
	return current;
}
