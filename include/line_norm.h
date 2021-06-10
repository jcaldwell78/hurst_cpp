
#ifndef _LINE_NORM_H_
#define _LINE_NORM_H_

#include "line.h"

/**
  Normalized linear interpolation wavelet (see comment for
  the normalize function).

 */
template <class T>
class line_norm : public line<T> {

protected:
  /**
    The normalization step assures that each step of the wavelet
    transform has the constant "energy" where energy is defined as

    <pre>
    double energy = 0.0;
    for (int n = 0; n < N; n++) {
       energy = energy + (a[i] * a[i]);
    }
    </pre>

    See 5.2.1 of <i>Ripples in Mathematics</i> by Jensen
    and la Cour-Harbo

    The most common implementation of the Haar transform leaves out
    the normalization step, since it does not make much of a
    difference in many cases.  However, in the case of the wavelet
    packet transform, many of the cost functions are squares, so
    normalization produces smaller wavelet values (although the
    scaling function values are larger).  This may lead to a better
    wavelet packet result (e.g., a few large values and lots of small
    values).

    Normalization does have the disadvantage of destroying the
    averaging property of the Haar wavelet algorithm.  That is, the
    final scaling factor is no longer the mean of the time series.

   */
  void normalize( T& vec, int N, transDirection direction )
  {
    const double sqrt2 = sqrt( 2.0 );
    int half = N >> 1;

    for (int i = 0; i < half; i++) {
      int j = i + half;

      if (direction == forward) {
	vec[i] = sqrt2 * vec[i];
	vec[j] = vec[j]/sqrt2;
      }
      else if (direction == inverse) {
	vec[i] = vec[i]/sqrt2;
	vec[j] = sqrt2 * vec[j];
      }
      else {
	printf("normalize: bad direction value\n");
      }
    } // for
  } // normalize

  /**
    One inverse wavelet transform step, with normalization
   */
  void inverseStep( T& vec, const int n )
  {
    normalize( vec, n, inverse );
    update( vec, n, inverse );
    predict( vec, n, inverse );
    merge( vec, n );
  }  // inverseStep

  /**
    One step in the forward wavelet transform, with normalization
   */
  void forwardStep( T& vec, const int n )
  {
    split( vec, n );
    predict( vec, n, forward );
    update( vec, n, forward );
    normalize( vec, n, forward );
  } // forwardStep

};

#endif
