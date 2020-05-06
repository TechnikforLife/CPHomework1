// Die folgenden Befehle müssen im Verzeichnis, 
// in dem die "Makefile" liegt ausgeführt werden:
// make
// make calc
// Nico Dichter, Florian Giefer
// Die Plots können mit "make plot" erstellt werden.
/** 
 *  @file h1_electricpot.h
 *  @brief Provides functions for homework1 part1
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 *  @date 01.05.20	Moved f_i_integral1 and solveintegral_part1 into this modul
 *  @date 06.05.20	Renamed f_i_integral1 to integrant_H12
 * 					Renamed solveintegral_part1 to solveintegral_H12
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

/** @fn double integrant_H12(double * variables);
 * @brief Provides integrant for H1.2
 * 
 * @param variables		Array of variables to be used in the evaluation 
 * 						of the function value at the given point
 */
double integrant_H12(double * variables);



/** @fn double solveintegral_H12(double*variables);
 * @brief Solves the first integral (H1.2) with the given values for "variables"
 * 
 * @param variables		Array of variables to be used in the integration 
 * 						of the function
 */
double solveintegral_H12(double*variables);
#endif //ifndef H1_ELECTRICPOT_H