
/*! \file

  Run Hurst exponent extimation calculations on n-day returns (e.g.,
  1-day, 2-day, ... 30-day returns).  By hacking around with the code
  in hurst_stocks.cpp a range of n-day returns can be calculated for a
  single stock or the returns can be calculated on a table of stocks.
  See the documentation in the hurst_stocks.h and hurst_stocks.cpp
  code (or see the doxygen generated documentation).

 */
#include "hurst_stocks.h"

int
main()
{
  const char *path = "..\\data\\equities\\";
  hurst_stocks t( path );
  t.test();
  return 0;
}
