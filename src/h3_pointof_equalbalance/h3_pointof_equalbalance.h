/** 
 *  @file h3_pointof_equalbalance.h
 *  @brief Provides functions for homework1 part2
 *  @author Dichter nd@nocoffeetech.de
 *  @author Giefer 
 * 
 *   
 *  @date 03.05.20	Moved potentialH3, electricfieldsH3 and rootsecant 
 *  				into this modul
 * 
 *  @todo -
 * 
 *  @test -
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1
 */

#ifndef H3_POINTOF_EQUALBALANCE_H
#define H3_POINTOF_EQUALBALANCE_H

/** @fn double symfirstderivative(double h,double (*fp)(double*),
 * 							double* variables);
 * @brief Calculates the derivative of "fp" at "variables[0]"
 * 
 * Estimates the derivative of "fp" at "variables[0]" to precision of 1e-8.
 * The rest of "variables" can be set to the desired values in advance.
 * 
 * @param h				Start value for the stepsize
 * @param fp			Function to be derived
 * @param variables		Array of variables to be used in the calculation 
 * 						of the derivative
 */
double potentialH3(double *variables);
double electricfieldsH3(double *variables);
double rootsecant(double a,double b,double (*fp)(double*),double precision, 
				  double *variables);
#endif //ifndef H3_POINTOF_EQUALBALANCE_H