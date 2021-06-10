
#ifndef _HISTOGRAM_H_
#define _HISTOGRAM_H_

#include <assert.h>

/**
  Support for calculating histograms.

  The histogram class constructor is initialized with the number of
  bins to be used in the histogram.

  Each bin is a histo_bin object which contains information on the
  start and end value of the bin range and the frequency in the bin.
  The frequency is the number of values in the data set which
  are greater than or equal to start and less than end.

  Example:

  Given an array of 20 double values, calculate the histogram.  The
  data does not need to be in sorted order.  The histogram calculation
  will sort it.  A vector of histo_bin objects is allocated by the
  histogram::bin_vec class constructor.  The data, number of elements
  in the data set and the vector of histogram bins is passed to the
  histogram calculate function.  This will initialize each of the
  histogram bins with a start, end and frequency.

<pre>
    const size_t num_bins = 20;
    histogram::bin_vec binz( num_bins );
    histogram histo;

    histo.calculate( data, N, binz );

    for (size_t i = 0; i &lt; num_bins; i++) {
      size_t freq = static_cast<size_t>( binz[i] );
      printf("%7.4f %2d\\n", binz.start(i), freq );
    }
</pre>

  Note that binz[i] returns the frequency as a double, which is
  cast to a size_t value.

 */
class histogram
{
private:
  // copy constructor
  histogram( const histogram &rhs );

  class bin_vec;
  void init_bins( bin_vec &bins,
		  const double min,
		  const double max );

  /**
    Get values from a double array.
    */
  class value_pool
  {
  private:
    size_t ix_;
    const double *vec_;
    const size_t N_;

  public:
    value_pool( const double *vec, size_t N ) : vec_( vec ), N_( N )
    {
      ix_ = 0;
    }

    bool get_val( double &val )
    {
      bool rslt = false;
      val = 0.0;
      if (ix_ < N_) {
	rslt = true;
	val = vec_[ ix_ ];
	ix_++;
      }
      return rslt;
    } // get_val

  }; // value_pool

public:
  /**
    A histogram bin

    In a standard histogram a bin always contains a positive integer
    frequency (a.k.a. count of elements).  This histogram bin object
    is designed to be operated on a floating point wavelet
    transform.  So the frequency element is a double.

   */
  class histo_bin
  {
  private:
    /** number of values, v, such that start <= v < end */
    double frequency_;
    /** start of bin value range */
    double start_;
    /** end of bin value range */
    double end_;

  public:
    histo_bin() {}
    ~histo_bin() {}

    double frequency() { return frequency_; }
    void frequency( const double f ) { frequency_ = f; }

    double &freqPtr() { return frequency_; }

    double start() { return start_; }
    void start( const double s ) { start_ = s; }

    double end() { return end_; }
    void end( const double e ) { end_ = e; }

  }; // class histo_bin


  /**
    An array of histogram bins.

    This class overloads the array index operator [].  For an
    instance of bin_vec named binz, binz[i] will return the
    frequency value at index i.

    The class constructor is passed a value for the number of
    bin_vec elements.  It dynamically allocates an internal array.
    
    The class destructor deallocates the internal array.

    The start and end values for a given bin are referenced
    via the start and end functions.

   */
  class bin_vec
  {
  private:
    bin_vec( const bin_vec &rhs );
    const size_t num_bins;
    histo_bin *bins;

  public:
    bin_vec( size_t N ) : num_bins( N )
    {
      bins = new histo_bin[ num_bins ];
    }

    ~bin_vec()
    {
      delete [] bins;
    }

    size_t length() { return num_bins; }

    double start( const size_t i ) 
    { 
      assert( i < num_bins );
      return bins[i].start(); 
    }

    void start( const size_t i, const double val )
    {
      assert( i < num_bins );
      bins[i].start( val );
    }

    double end( const size_t i ) 
    { 
      assert( i < num_bins );
      return bins[i].end(); 
    }

    void end( const size_t i, const double val )
    {
      assert( i < num_bins );
      bins[i].end( val );
    }

    /** LHS [] operator */
    double &operator[]( const size_t i )
    {
      assert( i < num_bins );
      
      return bins[i].freqPtr();
    }

    /** RHS [] operator */
    double operator[]( const size_t i ) const
    {
      assert( i < num_bins );
      return bins[i].frequency();
    }

  }; // class bin_vec

public:
  histogram() {}
  ~histogram() {}

  void calculate( const double *raw_data,
		  const size_t N,
		  bin_vec &binz );
}; // histogram


#endif
