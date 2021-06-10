
#include <vector>

#include "spectrum.h"
#include "hurst_spectrum.h"
#include "haar.h"
#include "line_norm.h"
#include "daub.h"

using namespace std;

/**

   Calculate the wavelet power spectrum.

   The wavelet power spectrum is calculated from the result of the
   wavelet transform.  The wavelet transform results in a set of
   "octaves" which with a power of two number of wavelet coefficients.
   The power for a given octave is the sum of the squares of the
   wavelet coefficients in each octave.

<pre>
     P<sub>i</sub> = 0;
     for (j = octave_start; j &lt; octave_end; j++) {
        P<sub>i</sub> = P<sub>i</sub> + v<sub>j</sub><sup>2</sup>
     }
</pre> 

   Where P<sub>i</sub> is the power for octave <i>i</i>

   The octaves span the array index regions:

<pre>
      region  size  octave (power)
       1..1     1      0
       2..3     2      1
       4..7     4      2
       8..15    8      3
       16..31  16      4
         etc...
</pre>

   Note that element zero (v<sub>0</sub>) is a low pass value, so it
   is not used.

 */
void hurst_spectrum::spectrum_calc_( const double *v, 
				     const size_t N,
				     std::vector<double> &powerSpectrum )
{
  //
  // Normalized wavelets
  //
  haar<double *> w;
  // line_norm<double *> w;
  // Daubechies<double *> w;

  double *data = new double[ N ];
  for (size_t i = 0; i < N; i++)
    data[i] = v[i];

  w.forwardTrans( data, N );

  spectrum::spectralCalc( data, N, powerSpectrum );
  delete [] data;
} // spectrum_calc


/**
  
  Estimate the Hurst exponent using the wavelet transform.

  The Wavelet method for estimating the Hurst exponent must, as 
  far as I can tell, use an energy normalized version of the
  wavelet transform.  The Daubechies transform is energy normalized
  but the classic version of the Haar wavelet is not (although the
  version used here is).

  The wavelet transform is calculated for the data set for which
  the Hurst exponent is being estimated.  The normalized power
  is calculated for each octave.  In the code below the normalized
  power is calculated by first calculating the unnormalized power
  and then dividing by the number of wavelet coefficients in that
  octave (which will be 2<sup>j</sup>).  This yields the power
  spectrum.

  The log of the normalized power spectrum values is paired with the
  log of the size of the octave (e.g., j =
  log<sub>2</sub>(2<sup>j</sup>)), producing a set of points.  A 
  linear regression line is plotted through the points.  The
  estimate for the Hurst exponent, H is

<pre>
      H = abs( (slope-1) / 2 )
</pre>
  
  The power spectrum result is used from octave 3 (size = 8).

 */
void hurst_spectrum::calc_hurst_est( const double *v, 
				     const size_t N,
				     hurstInfo &info )
{
  vector<double> powerSpectrum;

  spectrum_calc_( v, N, powerSpectrum );

  const size_t numPts = powerSpectrum.size();
  size_t power = 8;

  (info.points()).clear();
  for (size_t octave = 3; octave < numPts; octave++) {
    double normPower = powerSpectrum[octave] / static_cast<double>(power);
    double logPower = log2( normPower );
    (info.points()).push_back( lregress::point( octave, logPower ) );
    power = power << 1;
  }

  // print_regression_points( info.points() );
  // printf("\n\n");

  lregress lr;

  lregress::lineInfo lineInfo;
  lr.lr( info.points(), lineInfo );

  double slope = lineInfo.slope();
  double intercept = lineInfo.intercept();
  double slopeError = lineInfo.slopeErr();

  info.slope( slope );
  info.slopeErr( slopeError );
  info.intercept( intercept );
} // hurst_calc
