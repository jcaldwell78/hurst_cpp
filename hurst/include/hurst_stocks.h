
#ifndef HURST_STOCKS_H
#define HURST_STOCKS_H

#include "hurst_test_base.h"

/**
   Test the rescaled range algorithm on stock returns.
 */
class hurst_stocks : public hurst_test_base
{
private:
  hurst_stocks( const hurst_stocks &rhs );

public:
  hurst_stocks( const char *path ) : hurst_test_base( path ) {}
  ~hurst_stocks() {}

  void test();
}; // hurst_stocks

#endif
