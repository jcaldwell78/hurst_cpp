
#ifndef HURST_BASE_H
#define HURST_BASE_H

#include <math.h>

#include <vector>

#include "lregress.h"

/**
   Abstract base class for Hurst exponent calculation.

   This base class defines the local hurstInfo class which
   is a container for the linear regression data calculated
   either through the R/S or wavelet spectrum points.  The
   base class also provides some utility functions: log2
   (log, base 2) and print_regression_points, which was
   used for debugging and printing data for plot creation
   (e.g., the plots on the associated web pages).

The
   base class also defines the calc_hurst_est interface
   (e.g., virtual function).

 */
class hurst_base {
protected:
  static double log10of2;
  double log2( const double val ) const
  {
    return log10( val )/ log10of2;
  }

  void print_regression_points( std::vector<lregress::point> data );

public:
  class hurstInfo {
  private:
    double slope_;
    double intercept_;
    double slopeErr_;
    std::vector<lregress::point> points_;

    hurstInfo( const hurstInfo &rhs );
  public:
    hurstInfo() 
    {
      slope_ = 0;
      slopeErr_ = 0;
    }
    ~hurstInfo() {};

    double slope() { return slope_; }
    void slope( double s ) { slope_ = s; }
    
    double slopeErr() { return slopeErr_; }
    void slopeErr( double se ) { slopeErr_ = se; }

    double intercept() { return intercept_; }
    void intercept( double intr ) { intercept_ = intr; }

    std::vector<lregress::point> &points() { return points_; }
  }; // class hurstInfo

  hurst_base() {};
  ~hurst_base() {};
  virtual void calc_hurst_est( const double *v, 
			       const size_t N, 
			       hurstInfo &info ) = 0;
}; // hurst_base

#endif
