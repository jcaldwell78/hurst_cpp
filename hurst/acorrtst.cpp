
/*! \file

  Test for the autocorelation function

 */

#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "yahooTS.h"

#include "autocorr.h"

const size_t days = 10;
// 2**10
const size_t N = 1024 + days;
// const size_t N = 1024;
// 2**9
// const size_t N = 512;

static double v[ N ];
static double returns[ N-days ];

// static double v[] = {
// #include "data/brown72.h"
  // #include "data/franses_data/data7.h"
  // #include "data/fgn8.h"
// };
//
// const size_t N = sizeof( v ) / sizeof( double );


int
main()
{
  autocorr acor(0.01, 256);
  autocorr::acorrInfo info;
  size_t i;
  /**
  acor.ACF( v, N, info );

  const size_t len = info.points().size();
  for (i = 0; i < len; i++) {
    printf("%7.4f\n", (info.points())[i] );
  }
  printf("slope = %7.4f\n", info.slope() );
  **/

  yahooTS ts( "..\\data\\equities\\" );
  
  size_t n = N;
  if (ts.getTS( "aa.csv", v, n, yahooTS::Close )) {
    assert( n == N );

    for (i = days; i < N; i++) {
      // returns[i-1] = (v[i] - v[i-1])/v[i-1];
      returns[i-days] = log(v[i]) - log(v[i-days]);
      // printf("%9.6f\n", returns[i-days] );
    }

    acor.ACF( returns, N, info );

    const size_t len = info.points().size();
    for (i = 0; i < len; i++) {
      printf("%7.4f\n", (info.points())[i] );
    }

    // printf("slope = %7.4f, slopeErr = %7.4f\n", info.slope(), info.slopeErr());
  }
  else {
    fprintf(stderr, "main: getTS failed\n");
  }

  return 0;
}
