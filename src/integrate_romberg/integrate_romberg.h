/** 
 *  @file integrate_romberg.h
 *  @brief Provides functions,to integrate functions
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 28.04.20	First Implementation of:
 * 					integratetrapez_posinf,idxc,
 * 					integrate_romberg,romberg_converge_check
 * 
 *  @todo -
 * 
 *  @test -
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1 
 */

#ifndef INTEGRATE_ROMBERG_H
#define INTEGRATE_ROMBERG_H
/** @fn double integrate(double* weights,double* x_sampling_points,int n,
 * 						double (*fp)(double));
 * @brief Approximates the integral of "fp"
 * 
 * Approximates the integral of "fp" using the given weights and steps
 * 
 * @param weights	Array of the weights for the sampling points
 * @param x_sampling_points	Array of sampling points
 * @param n		Amount of sampling points
 * @param fp	Math function pointer to function to integrate
 */
double integratetrapez_posinf(double lowerboundary,
					   double (*fp)(double*),double subintervalllength,
					   double* variables,double relprecision);
int idxc(int i,int k, int* m_max_ptr);

double integrate_romberg(double start,double end,double (*fp)(double*),
					   double* variables,int m_max,int n_0,double relprecision,
						 int* stepsused,int endisinf);
double romberg_converge_check(double * variables,double lowerboundary,
						double upperboundary,double(*fp)(double*),
						double relprecision,int n_0,int endisinf);


#endif //ifndef INTEGRATE_ROMBERG_H