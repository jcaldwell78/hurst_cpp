
#include <assert.h>
#include <stdio.h>


#include <lregress.h>

using namespace std;

/** \file

    The data values are from Table 6.1 in "Statistics Manual" by Crow,
    Davis, Maxfield, Dover Press.

    According to "Statistics Manual" 

<pre>
         b = 7.35476

         a = -337.983
</pre>

    for the equation y' = a + bx

 */



/**
   Initialize the data vector container with data from the
   X and Y vectors.
 */
void init_data( vector<lregress::point> &data )
{
  static double X[] = { 55.77,
			55.05,
			54.27,
			50.63,
			49.86,

			53.04,
			51.33,
			56.70,
			55.07,
			55.76,
	       
			54.40,
			55.39,
			57.49,
			57.56,
			58.76,
	       
			59.32,
			57.21,
			68.55,
			65.04,
			66.98,

			63.69,
			58.34 };

  static double Y[] = { 83.9,
			66.4,
			73.1,
			66.7,
			30.1,
	       
			36.2,
			22.8,
			66.5,
			37.0,
			58.0,

			71.9,
			83.1,
			66.2,
			72.3,
			65.8,

			123.5,
			116.8,
			160.1,
			158.2,
			152.2,

			134.8,
			87.3 };

  const size_t N = sizeof( X ) / sizeof( double );
  assert( N == (sizeof( Y ) / sizeof(double)) );

  size_t i;
  for (i = 0; i < N; i++) {
    lregress::point p( X[i], Y[i] );
    data.push_back( lregress::point( p ) );
  }
} // init_data


main()
{
  lregress lr;
  lregress::lineInfo info;

  vector<lregress::point> data;
  init_data( data );
  const size_t N = data.size();

  size_t i;
  // print out the points
  for (i = 0; i < N; i++) {
    // printf("%7.4f  %7.4f\n", data[i].x(), data[i].y() );
  }

  lr.lr( data, info );

  printf("b (slope) = %7.4f, a (intercept) = %7.4f\n", 
	 info.slope(), 
	 info.intercept()
	 );
  printf(" slopeErr = %7.4f, stddev = %7.4f, corr = %7.4f\n",
	 info.slopeErr(), info.stddev(), info.corr() );

  double yPrime;
  for (i = 0; i < N; i++) {
    yPrime = info.intercept() + (info.slope() * data[i].x());
    // printf("%7.4f  %7.4f\n", data[i].x(), yPrime );
  }

} // main
