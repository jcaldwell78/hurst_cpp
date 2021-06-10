
#ifndef HURST_SPECTRUM_H
#define HURST_SPECTRUM_H

#include "hurst_base.h"

/**
   Estimate the Hurst exponent using the wavelet transform.

 */
class hurst_spectrum : public hurst_base
{
private:
  void spectrum_calc_( const double *v, 
		       const size_t N,
		       std::vector<double> &powerSpectrum );
public:
  void calc_hurst_est( const double *v, const size_t N, hurstInfo &info );
}; 

#endif
