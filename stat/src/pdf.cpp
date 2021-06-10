
#include <stdio.h>
#include "pdf.h"


void pdf::normalize( double *norm, const double *v, const size_t N )
{
  double sum = 0;
  size_t i;
  for (i = 0; i < N; i++) {
    sum = sum + v[i];
  }
  double mean = 0;
  if (sum != 0) {
    double mean = sum / N;
  }
  for (i = 0; i < N; i++)
    norm[i] = v[i] - mean;
} // normalize



double pdf::pdf_stddev( const double *v, const size_t N )
{
  double pdf_sigma = 0.0;
  if (v != 0 && N != 0) {
    // On average, 4 elements per bin
    // const size_t num_bins = N >> 2;
    const size_t num_bins = 64;
    histogram::bin_vec binz( num_bins );
    histogram histo;

    histo.calculate( v, N, binz );
    double *freq = new double[ num_bins ];

    // calculate the PDF from the integer frequency counts
    for (size_t i = 0; i < num_bins; i++) {
      freq[i] = 0.0;
      size_t count = static_cast<size_t>( binz[i] );
      double val = 0.0;
      if (count > 0) {
	freq[i] = static_cast<double>(count)/static_cast<double>(N);
	val = freq[i];
      }
      // printf("%2d %9.6f\n", i, val );
    }
    // printf("\n\n");

    double *norm = new double[ num_bins ];

    normalize(norm, freq, num_bins);

    stddev sd;
    pdf_sigma = sd.sd( norm, num_bins );

    delete [] norm;
    delete [] freq;
  }
  return pdf_sigma;
} // pdf
