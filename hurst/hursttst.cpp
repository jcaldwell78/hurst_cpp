
/*! \file

  Test the classic rescaled range (R/S) algorithm on synthetic
  data sets.

 */

#include <assert.h>
#include <stdio.h>

#include "rescaled_range.h"

/**
   Initialize an array with synthetic data set values
 */
static double v[] = {
  // Test data set with a Hurst value of 7.2
#include "data/brown72.h"
  // Test data set with a Hurst value of 8.0
  // #include "data/fgn8_1024.h"
};

// Number of elements
const size_t N = sizeof( v ) / sizeof( double );


int
main()
{
  rescaled_range hurst;
  rescaled_range::hurstInfo info;

  size_t n = N;  

  hurst.calc_hurst_est( v, n, info );

  const size_t len = (info.points()).size();
  for (size_t i = 0; i < len; i++) {
    printf("%7.4f  %7.4f\n", (info.points())[i].x(), (info.points())[i].y());
  }
  printf("slope = %7.4f +- %7.4f, intercept = %7.4f\n", 
	 info.slope(), info.slopeErr(), info.intercept() );
  return 0;
}
