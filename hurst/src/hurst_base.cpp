
#include "hurst_base.h"

using namespace std;

double hurst_base::log10of2 = log10( 2.0 );

void hurst_base::print_regression_points( vector<lregress::point> data )
{
  const size_t numPts = data.size();

  size_t i;
  for (i = 0; i < numPts; i++) {
    printf("%7.4f  %7.4f\n", data[i].x(), data[i].y() );
  }
} // print_regression_points


