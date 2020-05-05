/** 
 *  @file h2_electricfield.h
 *  @brief Provides functions for homework1 part2
 *  @author Dichter nd@nocoffeetech.de
 *  @author Giefer 
 * 
 *   
 *  @date 03.05.20	Moved symfirstderivative, e_field_part2, diffintegrantH2_2 
 *  				and solveH22 into this modul
 * 
 *  @todo -
 * 
 *  @test -
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1
 */

#ifndef H2_ELECTRICFIELD_H
#define H2_ELECTRICFIELD_H

/** @fn double symfirstderivative(double h,double (*fp)(double*),
 * 							double* variables);
 * @brief Calculates the derivative of "fp" at "variables[1]"
 * 
 * Estimates the derivative of "fp" at "variables[1]" to precision of 1e-8,
 * using the symetric approximation.
 * The rest of "variables" can be set to the desired values in advance.
 * 
 * @param h				Start value for the stepsize
 * @param fp			Function to be derived
 * @param variables		Array of variables to be used in the calculation 
 * 						of the derivative
 */
double symfirstderivative(double h,double (*fp)(double*),double* variables);



/** @fn double e_field_part2(double* variables);
 * @brief Calculates the E-field for H2
 * 
 * Estimates the E-field for H2 using "symfirstderivative" 
 * and the given set of values for the variables
 * 
 * @param variables		Array of variables to be used in the calculation 
 */
double e_field_part2(double* variables);



/** @fn double diffintegrantH2_2(double* variables);
 * @brief Provides integrant for H2.2
 * 
 * @param variables		Array of variables to be used in the calculation 
 */
double diffintegrantH2_2(double* variables);



/** @fn double solveH22(double*variables);
 * @brief Solves the integral for H2.2 with the given values for "variables"
 * 
 * @param variables		Array of variables to be used in the integration 
 * 						of the function
 */
double solveH22(double*variables);
#endif //ifndef H2_ELECTRICFIELD_H