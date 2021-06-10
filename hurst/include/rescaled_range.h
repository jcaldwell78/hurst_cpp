
#ifndef RESCALED_RANGE_H
#define RESCALED_RANGE_H

#include <math.h>

#include <vector>

#include "hurst_base.h"

/**
   Estimate the hurst exponent using the rescaled range technique
   
 */
class rescaled_range : public hurst_base
{
private:
  double calc_mean_( const double *v, const size_t N);
  double calc_RS_( const double *v, 
		   const size_t N );

  double calc_RS_ave_( const double *v, 
		       const size_t N, 
		       const size_t box_size );

public:

  void calc_hurst_est( const double *v, 
		       const size_t N, 
		       hurst_base::hurstInfo &info );
}; // class rescaled_range

#endif
