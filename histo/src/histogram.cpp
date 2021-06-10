
#include <stdio.h>

#include "dbl_sort.h"
#include "histogram.h"


/**
  Initialize the histogram bin array
 */
void histogram::init_bins( bin_vec &bins,
			   const double min,
			   const double max )
{
  size_t num_bins = bins.length();
  double range = max - min;
  double bin_size = range / static_cast<double>( num_bins );

  double start = min;
  double end = min + bin_size;

  for (size_t i = 0; i < num_bins; i++) {
    bins[i] = 0;           // initialize frequency to zero
    bins.start(i, start ); // initialize the i'th bin start value
    bins.end(i, end );     // initialize the i'th bin end value
    start = end;
    end = end + bin_size;
  }
  // The frequency in a bin is incremented if a value v is
  // in the range start <= v < end.  This is fine until 
  // we reach the last bin, which should also get values
  // which are in the range start <= v <= end.  So add a
  // small amount to the end value to assure that the
  // end value of the last bin is beyond the value range.
  bins.end(num_bins-1, bins.end(num_bins-1) + (bin_size / 10.0) );
} // init_bins



/**
  Calculate a histogram

  \param raw_data The raw data from which to calculate the histogram

  \param N The number of data values in <i>raw_data</i>

  \param bins An array of histo_bin objects

  \param num_bins The number of histogram bins (number of elements in histo_bin)

 */
void histogram::calculate( const double *raw_data,
			   const size_t N,
			   bin_vec &bins )
{
  double *sort_data = new double[ N ];

  for (size_t i = 0; i < N; i++) {
    sort_data[i] = raw_data[i];
  }
    
  dbl_sort s;

  s.sort( sort_data, N );
  double min = sort_data[0];
  double max = sort_data[N-1];

  size_t num_bins = bins.length();

  init_bins( bins, min, max );

  value_pool pool( sort_data, N );

  size_t bin_ix = 0;

  double val;
  bool more_values = pool.get_val( val );
  double end = bins.end(bin_ix);

  while (bin_ix < num_bins && more_values) {
    if (val < end) {
      bins[bin_ix] = bins[bin_ix] + 1; // increment the frequency
      more_values = pool.get_val( val );
    }
    else {
      bin_ix++;
      end = bins.end(bin_ix);
    }
  } // while

  delete [] sort_data;
} // calculate

