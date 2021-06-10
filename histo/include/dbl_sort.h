
#ifndef _DBL_SORT_H_
#define _DBL_SORT_H_

#include "generic_sort.h"

class dbl_sort : public generic_sort<double>
{
  protected:

  int compare( double a, double b)
  {
    int rslt = 0;

    if (a < b)
      rslt = -1;
    else if (a > b)
      rslt = 1;

    return rslt;
  } // compare


}; // dbl_sort


#endif
