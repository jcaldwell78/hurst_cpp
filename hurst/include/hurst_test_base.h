
#ifndef HURST_TEST_BASE_H
#define HURST_TEST_BASE_H

#include "yahooTS.h"

/**

   My software to estimate the Hurst exponent was originally
   developed to estimate the Hurst exponent of stock market
   time series (e.g., n-day returns etc...).  The hurst_test_base
   supports reading finance.yahoo.com time series files (in 
   spread sheet data format).  Subclasses can then be derived from
   this class to calculate the Hurst exponent (via the reseacled
   range or via wavelets) or other statistics (autocorrelation)
   on the time series.

 */
class hurst_test_base
{
private:
  /** Disallow the copy constructor */
  hurst_test_base( const hurst_test_base &hurst_test_base );

protected:
  /** The yahooTS object <i>ts</i> supports reading and
      simple parsing of the finance.yahoo.com time series
      file */
  yahooTS ts;

  /**
     A container for the information for a given stock: the
     company name, the name of the file containing the 
     stock market data and the stock market "ticker" (e.g.,
     market symbol).
   */
  class equityEntry
  {
    /** company name */
    const char *name_;
    /** file name for data */
    const char *file_;
    /** market symbol */
    const char *ticker_;
  public:
    equityEntry( const char *n, 
		 const char *tic,
		 const char *phile ) : name_(n), ticker_(tic), file_(phile) {}
    equityEntry( const equityEntry &rhs )
    {
      name_ = rhs.name_;
      file_ = rhs.file_;
      ticker_ = rhs.ticker_;
    }
    ~equityEntry() {}
    const char *name() { return name_; }
    const char *file() { return file_; }
    const char *ticker() { return ticker_; }
  }; // class equityEntry

  /** A table of stocks that are going to be processed */
  static equityEntry equityTable_[];
  /** The size of the table */
  static const size_t tableSize_;

protected:
  size_t blockedPercentReturn( const double *v,
			 double *ret,
			 const size_t N,
			 const size_t block_size );

  size_t blockedLogReturn( const double *v,
			 double *ret,
			 const size_t N,
			 const size_t block_size );

  equityEntry &findTableEntry( const char *ticker );

public:
  hurst_test_base( const char *path ) : ts( path ) {}
  ~hurst_test_base() {}

  virtual void test() = 0;
}; // hurst_test_base

#endif
