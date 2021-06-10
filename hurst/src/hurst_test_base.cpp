
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "hurst_test_base.h"

/**
   Initialize a table of company names, stock tickers and
   file names (the *.csv is the file that is downloaded
   from finance.yahoo.com).
 */
hurst_test_base::equityEntry hurst_test_base::equityTable_[] = 
{ hurst_test_base::equityEntry( "Alcoa",        "aa",   "aa.csv" ),
  hurst_test_base::equityEntry( "Applied Mat.", "amat", "amat.csv"),
  hurst_test_base::equityEntry( "Boeing",       "ba",   "ba.csv" ),
  hurst_test_base::equityEntry( "Capital One",  "cof",  "cof.csv" ),
  hurst_test_base::equityEntry( "GE",           "ge",   "ge.csv" ),
  hurst_test_base::equityEntry( "General Mills","gis",  "gis.csv"),
  hurst_test_base::equityEntry( "IBM Corp.",    "ibm",  "ibm.csv" ),
  hurst_test_base::equityEntry( "Intel",        "intc", "intc.csv" ),
  hurst_test_base::equityEntry( "3M Corp.",     "mmm",  "mmm.csv" ),
  hurst_test_base::equityEntry( "Merck",        "mrk",  "mrk.csv"),
  hurst_test_base::equityEntry( "Wal-Mart",     "wmt",  "wmt.csv"),
};

const size_t hurst_test_base::tableSize_ = 
                sizeof( hurst_test_base::equityTable_ ) / sizeof( hurst_test_base::equityEntry );

/**
   Given a market "ticker" (equity symbol), return an equityEntry
   object containing the company name, the ticker and the file
   name.
 */
hurst_test_base::equityEntry &
hurst_test_base::findTableEntry( const char *ticker )
{
  for (size_t i = 0; equityTable_[i].ticker() != 0; i++) {
    if (strcmp(equityTable_[i].ticker(), ticker) == 0)
      break;
  } // for
  return equityTable_[i];
} // findTableEntry


/**
   Calculate the n-day log return:

   <pre>
     R<sub>i</sub> = log( P<sub>t</sub> ) - log( P<sub>t-n</sub> )
   </pre>
   
   where log() is the natural log.

   In the finance literature, log return is the most common method
   used to calculate the return.  By taking the log of the return
   the effect of overall market movement is minimized.
 */
size_t hurst_test_base::blockedLogReturn( const double *v,
					  double *ret,
					  const size_t N,
					  const size_t block_size )
{
  size_t ix = 0;
  for (size_t i = block_size; i < N; i = i + block_size) {
    ret[ix] = log(v[i]) - log(v[i-block_size]);
    // printf("%4d %9.6f\n", ix, ret[ix] );
    ix++;
  }  
  // printf("\n\n");
  return ix;
}

/**
   Calculate the n-day percentage return:

   <pre>
   R<sub>t</sub> = (P<sub>t</sub> - P<sub>t-n</sub>)/P<sub>t-n</sub>
   </pre>

   The percentage return is also used by some people building
   financial models.  I have not found that it makes much difference
   in my results when the percentage or log returns is used.  For 
   compatibility with the finance literature, I usually use log
   return.
   
 */
size_t hurst_test_base::blockedPercentReturn( const double *v,
					      double *ret,
					      const size_t N,
					      const size_t block_size )
{
  size_t ix = 0;
  for (size_t i = block_size; i < N; i = i + block_size) {
    ret[ix] = (v[i] - v[i-block_size]) / v[i-block_size];
    ix++;
  }  
  return ix;
}
