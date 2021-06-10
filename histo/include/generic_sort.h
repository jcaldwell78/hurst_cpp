
#ifndef _GENERIC_SORT_H_
#define _GENERIC_SORT_H_

/**

  An abstract generic sort class

  This is an abstract class.  The class that is derived from this
  class must define the <i>compare</i> function.  The <i>compare</i>
  function returns an integer value that is less than, equal or
  greater than zero depending on the result of the comparision (the
  function is modeled after UNIX strcmp).

  This class is based on the Java quicksort algorithm by
  James Gosling at at Sun Microsystems (see below).

  <blockquote>
  <p>
  QSortAlgorithm.java	1.3   29 Feb 1996 James Gosling
  </p>

  <p>
  Copyright (c) 1994-1996 Sun Microsystems, Inc. All Rights Reserved.
  </p>

  <p>
  Permission to use, copy, modify, and distribute this software
  and its documentation for NON-COMMERCIAL or COMMERCIAL purposes and
  without fee is hereby granted. 
  </p>

  <p>
  Please refer to the file http://www.javasoft.com/copy_trademarks.html
  for further important copyright and trademark information and to
  http://www.javasoft.com/licensing.html for further important
  licensing information for the Java (tm) Technology.
  </p>

  </blockquote>
  
  */

template<class T>
class generic_sort
{

private:
  /**
    Exchange element a[i] and a[j]
   */
  void swap(T *a, int i, int j)
  {
    T t;

    t = a[i];
    a[i] = a[j];
    a[j] = t;
  } // swap


  /** This is a generic version of C.A.R Hoare's Quick Sort 
   * algorithm.  This will handle arrays that are already
   * sorted, and arrays with duplicate keys.<BR>
   *
   * If you think of a one dimensional array as going from
   * the lowest index on the left to the highest index on the right
   * then the parameters to this function are lowest index or
   * left and highest index or right.  The first time you call
   * this function it will be with the parameters 0, a.length - 1.
   *
   * @param a       an integer array
   * @param lo0     left boundary of array partition
   * @param hi0     right boundary of array partition
   */
  void QuickSort(T *a, int lo0, int hi0)
  {
    int lo = lo0;
    int hi = hi0;
    T mid;
    
    if ( hi0 > lo0) {
      /* Arbitrarily establishing partition element as the midpoint of
       * the array.
       */
      mid = a[ ( lo0 + hi0 ) / 2 ];
      
      // loop through the array until indices cross
      while( lo <= hi )	{
	/* find the first element that is greater than or equal to 
	 * the partition element starting from the left Index.
	 */
	while( ( lo < hi0 ) && ( compare(a[lo], mid) < 0 ) )
	  ++lo;
	
	/* find an element that is smaller than or equal to 
	 * the partition element starting from the right Index.
	 */
	while( ( hi > lo0 ) && ( compare(a[hi], mid) > 0) )
	  --hi;
	
	// if the indexes have not crossed, swap
	if( lo <= hi ) {
	  swap(a, lo, hi);
	  
	  ++lo;
	  --hi;
	}
      } // while
      
      /* If the right index has not reached the left side of array
       * must now sort the left partition.
       */
      if( lo0 < hi )
	QuickSort( a, lo0, hi );
      
      /* If the left index has not reached the right side of array
       * must now sort the right partition.
       */
      if( lo < hi0 )
	QuickSort( a, lo, hi0 );
      
    }
  }  // QuickSort

protected:
  /**
    This is an abstract function that should be defined
    by the class derived from generic_sort.  This function
    is passed two objects, <i>a</i> and <i>b</i>.  It 
    compares them and should return the following values:

<pre>
    If (a == b) return 0
    if (a < b) return -1
    if (a > b) return 1
</pre>
   */
  virtual int compare( T a, T b) = 0;

private:
  generic_sort( const generic_sort &rhs );

public:
  generic_sort() {}
  ~generic_sort() {}

  void sort(T *a, size_t N)
  {
    QuickSort(a, 0, N-1);
  } // sort

}; // generic_sort

#endif
