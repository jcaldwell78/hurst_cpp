
#include <math.h>

#include "stddev.h"


/**
   Calculate the arithmetic mean (a.k.a. average)
 */
double stddev::calc_mean_( const double *v, const size_t N )
{
  double mean = 0.0;
  double sum = 0.0;

  for (size_t i = 0; i < N; i++) {
    sum = sum + v[i];
  }
  mean = sum / static_cast<double>(N);
  return mean;
} // calc_mean_


/**
   Calculate the standard deviation, given the mean of the numbers
 */
double stddev::sd( const double *v, 
		   const size_t N, 
		   const double mean )
{
  double stdDev = 0.0;
  mean_ = mean;

  // calculate the standard deviation sum
  double stdDevSum = 0;
  double x;
  for (size_t i = 0; i < N; i++) {
    x = v[i] - mean_;
    stdDevSum = stdDevSum + (x * x);
  }
  double variance = stdDevSum / static_cast<double>(N-1);
  stdDev = sqrt( variance );  
  return stdDev;
} // sd


/**
   Calculate the standard deviation of N values pointed to by v.  This
   is a so called "unbiased" estimate of the standard deviation.  
*/
double stddev::sd( const double *v, const size_t N )
{
  double stdDev = 0.0;
  if (v != 0) {
    double mean = calc_mean_(v, N);
    stdDev = sd( v, N, mean );
  }
  return stdDev;
} // sd

