
#include <assert.h>
#include <stdio.h>

#include "hurst_stocks.h"
#include "rescaled_range.h"


/**
   Test the rescaled range algorithm on stock returns.

   By hacking this code (e.g., uncommenting the commented
   parts and commenting out others) you can test the rescaled
   range on either a single stock over a range of n-day returns
   or you can test against the table of stocks (see the base
   class hurst_test_base).

   Sorry for the hackish nature of this code, but it worked
   for generating tests and the results on the Hurst 
   exponent web page.

 */
void hurst_stocks::test()
{
  const size_t days = 10;
  // const size_t ReturnSize = 1024;
  const size_t ReturnSize = 8192;
  // const size_t DataSize = ReturnSize + days;
  const size_t DataSize = 8192;

  // These arrays have to be static to get around some Microsoft
  // wierdness with large stack allocated arrays.
  static double data[ DataSize ];
  static double returns[ ReturnSize ];

  rescaled_range hurst;
  rescaled_range::hurstInfo info;

  //
  // To test a single return period against the table of stocks
  // uncomment this for loop and assign a single n-day return
  // period to blockSize.  Comment out the enclosed for loop
  // (see below).
  //
  //  for (size_t tableEntry = 0; tableEntry < tableSize_; tableEntry++) {
  //  const char *fileName = equityTable_[tableEntry].file();
    const char *fileName = "ibm_30year.csv";
    size_t n = DataSize;
    if (ts.getTS( fileName, data, n, yahooTS::Close )) {
      assert(n == DataSize );

      //
      // Comment out the for loop if you are calculating returns
      // on a table of stocks and use a fixed return period.
      // The return period is defined by blockSize.
      //
      for (size_t blockSize = 1; blockSize <= 30; blockSize++) {
	for (size_t i = 0; i < ReturnSize; i++)
	  returns[i] = 0;

	size_t numReturns;
	numReturns = blockedLogReturn( data, returns, DataSize, blockSize );

	hurst.calc_hurst_est( returns, numReturns, info );

	/**
	   for (size_t i = 0; i < ReturnSize; i++)
	   printf("%7.4f\n", returns[i] );
	**/

      // const char *companyName = equityTable_[tableEntry].name();

	const char *companyName = "IBM Corp.";
	/**
	printf("blockSize = %2d %-13s H est. = %7.4f +-%7.4f\n", 
	       blockSize,
	       companyName,
	       info.slope(), 
	       info.slopeErr());
	**/

	// printf("%2d %7.4f\n", blockSize, sigma );
	printf("%2d %7.4f\n", blockSize, info.slope());
      }

      /**
    }
    else {
      printf("Error opening file %s\n", fileName );
      break;
    }
      **/
  } // for
}
