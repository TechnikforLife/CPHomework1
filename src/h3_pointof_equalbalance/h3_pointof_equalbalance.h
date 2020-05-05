/** 
 *  @file h3_pointof_equalbalance.h
 *  @brief Provides functions for homework1 part3
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

/** @fn double potentialH3(double *variables);
 * @brief Calculates the potential needed in H3
 * 
 * @param variables		Array of variables to be used in the calculation 
 */
double potentialH3(double *variables);



/** @fn double electricfieldsH3(double *variables);
 * @brief Calculates the electricfield needed in H3
 * 
 * Uses "symfirstderivative" from "h2_electricfield.c" and "potentialH3".
 * 
 * @param variables		Array of variables to be used in the calculation 
 */
double electricfieldsH3(double *variables);



/** @fn double rootsecant(double a,double b,double (*fp)(double*),
 * 					double precision,double *variables);
 * @brief Calculates the root of "fp"
 * 
 * Calculates the root of "fp", using the secant method with the given 
 * start values, to the given relativ precision.
 * 
 * @param a				Lower Start value
 * @param b				Lower Start value
 * @param fp			Function to search root from
 * @param relprecision	Relative precision, that should be reached
 * @param variables		Array of variables to be used in the calculation 
 */
double rootsecant(double a,double b,double (*fp)(double*),double relprecision, 
				  double *variables);
#endif //ifndef H3_POINTOF_EQUALBALANCE_H