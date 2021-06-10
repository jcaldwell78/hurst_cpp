
#ifndef STDDEV_H_
#define STDDEV_H_

/**
  Calculate the unbiased standard deviation.


<h4>
   Copyright and Use
</h4>

   You may use this source code without limitation and without
   fee as long as you include:

<p>
<i>
     This software was written and is copyrighted by Ian Kaplan, Bear
     Products International, www.bearcave.com, 2001.
</i>
</p>

   This software is provided "as is", without any warranty or
   claim as to its usefulness.  Anyone who uses this source code
   uses it at their own risk.  Nor is any support provided by
   Ian Kaplan and Bear Products International.

   Please send any bug fixes or suggested source changes to:

<pre>
     iank@bearcave.com
</pre>

 */
class stddev
{
private:
  stddev( const stddev &rhs );

  double mean_;
  double calc_mean_( const double *v, const size_t N);
public:
  stddev() { mean_ = 0;}
  ~stddev() {}

  double mean() { return mean_; }
  /** calculate the standard deviation of N values in v */
  double sd( const double *v, 
	     const size_t N );

  /** calculate the standard deviation, given the mean */
  double sd( const double *v, 
	     const size_t N, 
	     const double mean );
};

#endif
