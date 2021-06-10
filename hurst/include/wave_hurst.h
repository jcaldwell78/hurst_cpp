
#ifndef WAVE_HURST_H
#define WAVE_HURST_H

#include "hurst_test_base.h"

/**
   Test class for running the wavelet Hurst estimator on
   a range of n-day returns.
 */
class wave_hurst : public hurst_test_base
{
private:
  wave_hurst( const wave_hurst &rhs );

public:
  wave_hurst( const char *path ) : hurst_test_base( path ) {}
  ~wave_hurst() {}

  void test();
}; // wave_hurst

#endif
