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
 *  @date 29.04.20	Fixed endless bug in integratetrapez_posinf
 * 
 *  @todo -
 * 
 *  @test -
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.2
 */

#ifndef INTEGRATE_ROMBERG_H
#define INTEGRATE_ROMBERG_H
/** @fn double integratetrapez_posinf(double lowerboundary,
 * 					   double (*fp)(double*),double subintervalllength,
 * 					   double* variables,double relprecision);
 * @brief Approximates the integral of "fp" from "lowerboundary" to infty
 * 
 * Approximates the integral of "fp" using the given step size and
 * the given array of variables(where variables[0])is the variable 
 * in which "fp" gets integrated.
 * 
 * @param lowerboundary			Lowerboundary of the integral
 * @param fp					Function to be integrated
 * @param subintervalllength	Step size
 * @param variables				Array of variables to be passed onto "fp"
 * @param relprecision			Relativ precision to be reached
 */
double integratetrapez_posinf(double lowerboundary,
					   double (*fp)(double*),double subintervalllength,
					   double* variables,double relprecision);



/** @fn int idxc(int i,int k, int* m_max_ptr);
 * @brief Calculates the memoryindex of the given i,k
 * 
 * Calculates the memoryindex of the given i,k in a Leville scheme.
 * 
 * @param i			First index of T_tilde
 * @param k			Second index of T_tilde
 * @param m_max_ptr	Amount of stages allocated
 */
int idxc(int i,int k, int* m_max_ptr);



/** @fn double integrate_romberg(double start,double end,double (*fp)(double*),
 * 					   double* variables,int m_max,int n_0,double relprecision,
 * 						 int* stepsused,int endisinf);
 * @brief Approximates the integral of "fp" using the romberg method
 * 
 * Approximates the integral of "fp" using the given "n_0" and
 * the given array of variables(where variables[0])is the variable 
 * in which "fp" gets integrated.
 * 
 * @param start			Lowerboundary of the integral
 * @param end			Upperboundary of the integral
 * @param fp			Function to be integrated
 * @param variables		Array of variables to be passed onto "fp"
 * @param m_max			Maximum amount of stages to be used
 * @param n_0			Start Amount of subintervalls
 * @param relprecision	Relativ precision to be reached
 * @param stagesused	Location to save how many stages were used
 * @param endisinf		Rather the upperboundary is infty
 */
double integrate_romberg(double start,double end,double (*fp)(double*),
					   double* variables,int m_max,int n_0,double relprecision,
						 int* stagesused,int endisinf);



/** @fn double romberg_converge_check(double * variables,double lowerboundary,
 * 						double upperboundary,double(*fp)(double*),
 * 						double relprecision,int n_0,int endisinf);
 * @brief Approximates the integral of "fp" using the romberg method
 * 
 * Approximates the integral of "fp" using the given "n_0" and
 * the given array of variables(where variables[0])is the variable 
 * in which "fp" gets integrated.The amount of stages to use gets 
 * automatically adjusted to reach the needed precision.
 * "integrate_romberg" gets used for the main integration part.
 * 
 * @param variables		Array of variables to be passed onto "fp"
 * @param lowerboundary	Lowerboundary of the integral
 * @param upperboundary	Upperboundary of the integral
 * @param fp			Function to be integrated
 * @param relprecision	Relativ precision to be reached
 * @param n_0			Start Amount of subintervalls
 * @param endisinf		Rather the upperboundary is infty
 */
double romberg_converge_check(double * variables,double lowerboundary,
						double upperboundary,double(*fp)(double*),
						double relprecision,int n_0,int endisinf);


#endif //ifndef INTEGRATE_ROMBERG_H