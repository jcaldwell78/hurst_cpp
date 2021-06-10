
#ifndef PDF_H
#define PDF_H

#include "stddev.h"
#include "histogram.h"

/**
  Calculate the probability denisty function from a set of
  data.

  This is a discrete version of the Probability Density Function
  (PDF), which for continuous functions can be expressed in
  non-discrete form.  Of course many of the things that we measure
  cannot be expressed as continuous functions.

  The PDF is a histogram, where each histogram bin represents the
  probability of the data being in the range over which the bin
  is calculated.  The sum of all the bins will be 1.

  The PDF is constructed so that it has a zero mean.  64 bins are used
  in calculating he histogram, so there should be sufficiently more
  than 64 items.

 */
class pdf
{
private:
  pdf( const pdf &rhs );
  void normalize( double *norm, const double *v, const size_t N );

public:
  pdf() {};
  ~pdf() {}

  double pdf_stddev( const double *v, const size_t N );
};

#endif
