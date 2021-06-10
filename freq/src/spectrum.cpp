
#include <vector>

#include "spectrum.h"

/**
  Calculate the wavelet power spectrum from the result of
  the wavelet transform.

  The spectrum is calculated by calculating the power for
  each of the wavelet coefficient bands.  The bands
  are ordered by increasing powers of two:
  2<sup>0</sup>, 2<sup>1</sup>, 2<sup>2</sup>...

  This is the unnormalized power spectrum.  The normalized
  power spectrum for band <i>j</i> divides the power by
  2<sup>j</sup>.

 */
void spectrum::spectralCalc( const double *a, 
			     const size_t N,
			     std::vector<double> &v )
{
  size_t end = 2;
  size_t start = 1;

  while (end <= N) {
    double power = 0;
    for (size_t i = start; i < end; i++) {
      power = power + (a[i] * a[i]);
    }
    v.push_back( power );
    start = end;
    end = end << 1;
  }
} // spectralCalc




/**
  Copy wavelet coefficient bands from <i>startBand</i>
  to <i>endBand</i>.

  Elements in the destination array that are not copied
  are set to zero.

 */
void spectrum::copyBands( double *dest,
			  const double *src,
			  const size_t N,
			  size_t startBand,
			  const size_t endBand )
{
  size_t end = 1;
  size_t start = 0;
  size_t bandCnt = 0;

  while (end <= N) {
    double power = 0;
    for (size_t i = start; i < end; i++) {
      if (bandCnt >= startBand && bandCnt <= endBand)
	dest[i] = src[i];
      else
	dest[i] = 0;
    }
    start = end;
    end = end << 1;
    bandCnt++;
  }
} // copyBands


