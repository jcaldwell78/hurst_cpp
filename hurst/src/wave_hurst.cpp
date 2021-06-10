
#include <assert.h>
#include <stdio.h>

#include "wave_hurst.h"
#include "rescaled_range.h"
#include "hurst_spectrum.h"

/**

   Run the wavelet Hurst exponent estimation algorithm against a range
   of returns.  For comparision the rescaled range is also run.  Note
   that the rescaled range algorithm does not necessarily require data
   with a power of two number of elements.  However, wavelet
   algorithms are limited to a power of two data set.

   This class mirrors the hurst_stocks class (they are both
   derived from the same base class).

<pre>
   1-day return  8192 values
   2-day return  4096 values
   4-day return  2048 values
   8-day return  1024 values
  16-day return   512 values
  32-day return   256 values
</pre>

 */
void wave_hurst::test()
{
  const size_t ReturnSize = 8192;
  const size_t DataSize = 8193;

  // These arrays have to be static to get around some Microsoft
  // wierdness with large stack allocated arrays.
  static double data[ DataSize ];
  static double returns[ ReturnSize ];

  //  for (size_t tableEntry = 0; tableEntry < tableSize_; tableEntry++) {
  //  const char *fileName = equityTable_[tableEntry].file();
    const char *fileName = "ibm_30year.csv";
    size_t n = DataSize;
    if (ts.getTS( fileName, data, n, yahooTS::Close )) {
      assert(n == DataSize );

      hurst_spectrum::hurstInfo waveInfo;
      hurst_spectrum wave;

      rescaled_range rs;
      rescaled_range::hurstInfo RSInfo;

      for (size_t blockSize = 1; blockSize <= 32; blockSize = (blockSize << 1)) {
	for (size_t i = 0; i < ReturnSize; i++)
	  returns[i] = 0;

	size_t numReturns;
	numReturns = blockedLogReturn( data, returns, DataSize, blockSize );

	wave.calc_hurst_est( returns, numReturns, waveInfo );
	rs.calc_hurst_est( returns, numReturns, RSInfo );

	double H = fabs( (waveInfo.slope() - 1)/ 2 );

	/**
	printf("points = %4d retSize = %2d ",
	       numReturns,
	       blockSize );
	printf(" H(w) = %7.4f +-%7.4f H(rs) = %7.4f +-%7.4f\n", 
	       H,
	       waveInfo.slopeErr(),
	       RSInfo.slope(),
	       RSInfo.slopeErr() );
	**/
	printf("%2d %7.4f\n", blockSize, RSInfo.slope() );
      }

      /**
    }
    else {
      printf("Error opening file %s\n", fileName );
      break;
    }
      **/
  } // for
}
