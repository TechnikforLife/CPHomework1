/** 
 *  @file h1_electricpot.h
 *  @brief Provides functions for homework1 part1
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 *  @date 01.05.20	Moved f_i_integral1 and solveintegral_part1 into this modul
 * 
 *  @todo -
 * 
 *  @test -
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1
 */

#ifndef H1_ELECTRICPOT_H
#define H1_ELECTRICPOT_H

/** @fn double f_i_integral1(double * variables);
 * @brief Provides integrant for H1.2
 * 
 * @param variables		Array of variables to be used in the evaluation 
 * 						of the function value at the given point
 */
double f_i_integral1(double * variables);



/** @fn double solveintegral_part1(double*variables);
 * @brief Solves the first integral (H1.2) with the given values for "variables"
 * 
 * @param variables		Array of variables to be used in the integration 
 * 						of the function
 */
double solveintegral_part1(double*variables);
#endif //ifndef H1_ELECTRICPOT_H