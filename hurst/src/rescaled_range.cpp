
#include "rescaled_range.h"

using namespace std;


/**
   Calculate the mean (average).
 */
double rescaled_range::calc_mean_( const double *v, const size_t N)
{
  double sum = 0.0;

  for (size_t i = 0; i < N; i++) {
    sum = sum + v[i];
  }
  double mean = sum / N;
  return mean;
} // calc_mean_


/**
   Calculate the rescaled range for a single region of data.
   
   \arg v a pointer to the start of the data region.

   \arg boxSize the size of the region (or box).
 */
double rescaled_range::calc_RS_( const double *v, 
				 const size_t boxSize )
{
  double RS = 0.0;
  if (v != 0 && boxSize > 0) {
    double min;
    double max;
    double runningSum;
    double runningSumSqr;

    double mean = calc_mean_( v, boxSize );

    min = 0.0;
    max = 0.0;
    runningSum = 0.0;
    runningSumSqr = 0.0;
    for (size_t i = 0; i < boxSize; i++) {
      double devFromMean = v[i] - mean;
      runningSum = runningSum + devFromMean;
      runningSumSqr = runningSumSqr + (devFromMean * devFromMean);
      if (runningSum < min)
	min = runningSum;
      if (runningSum > max)
	max = runningSum;
    }
    double variance = runningSumSqr / static_cast<double>(boxSize);
    double stdDev = sqrt( variance );

    double range = max - min;
    RS = range / stdDev;
  }
  
  return RS;
} // calc_RS


/**
   Calculate the R/S Average for the R/S values calculated on a set of
   "boxes" (regions) of size boxSize.

   This code is based on the assumption that boxSize is an integral
   multiple of N, the size of the array v.

   \arg v the data set used to estimate the Hurst exponent

   \arg N the size of the data set

   \arg boxSize the size of the region on which the R/S calculation
                is performed.  The R/S average is the average of
		the calculation on the set of regions.

 */
double rescaled_range::calc_RS_ave_( const double *v, 
				     const size_t N,
				     const size_t boxSize )
{
  size_t i;
  double stdDev;
  double range;
  double RS;
  double RSSum;
  double mean;
  double RSAve = 0.0;

  size_t numBoxes = N / boxSize; 
  if (numBoxes > 0) {
    RSSum = 0;
    for (i = 0; i+boxSize <= N; i = i + boxSize) {
      const double *boxStart = &v[i];
      RS = calc_RS_( boxStart, boxSize );
      RSSum = RSSum + RS;
    } // for i

    RSAve = RSSum / static_cast<double>( numBoxes );
  }
  
  return RSAve;
} // calc_RS_ave_



/**
   Estimate the Hurst exponent using the rescale range 
   calculation.

   The average rescaled range is calculated on a set of regions
   (sometimes referred to as "boxes") which are, in this case, a
   power of two in size (e.g., 8, 16, 32, ...).  The data set
   on which the Hurst exponent is estimated should be a power
   of two as well, so that there are an integral number of 
   "boxes".

   The log (base 2) of the RSAve is paired with the log of the region
   size to for a point.  A set of points is used to calculate a linear
   regression line.  The slope of this line is the estimate for the
   Hurst exponent.

   \arg v The data set on which the R/S calculation will be
          performed.

   \arg N The size of the data set.

   \arg info a reference variable which is returned with the
        information from the regression calculation (e.g.,
	slope, error of slope, etc).

  */
void rescaled_range::calc_hurst_est( const double *v, 
				     const size_t N,
				     hurst_base::hurstInfo &info )
{

  double hurstEst = 0.0;

  if (v != 0 && N > 0) {
    const size_t minBox = 8;

    (info.points()).clear();
    size_t boxSize;
    for (boxSize = N; boxSize >= minBox; boxSize = (boxSize >> 1)) {
      double RSAve = calc_RS_ave_( v, N, boxSize );
      double logRSAve = log2( RSAve );
      double logBoxSize = log2( boxSize );
      (info.points()).push_back( lregress::point( logBoxSize, logRSAve ) );
    }

    // print_regression_points( info.points() );

    lregress lr;

    lregress::lineInfo lineInfo;
    lr.lr( info.points(), lineInfo );

    double slope = lineInfo.slope();
    double intercept = lineInfo.intercept();
    double slopeError = lineInfo.slopeErr();

    info.slope( slope );
    info.slopeErr( slopeError );
    info.intercept( intercept );

    // printf("slope = %7.4f +- %7.4f, intercept = %7.4f\n", 
    // slope, slopeError, intercept );
  }
  
} // calc_hurst_est
