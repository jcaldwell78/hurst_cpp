
#include <stdio.h>

#include "stddev.h"

/** Table 1 from "Statistics Manual" by Crow et al 

    stddev = 220.6 (calculated here as 220.6428)
    mean = 1589.8

  */
double  data[] = {1472, 1315, 1984, 1900, 1646,
                  1709, 1780, 1571, 1681, 1453,
                  1799, 1372, 1420, 1612, 1546,
		  1255, 1818, 1357, 1412, 1775, 
                  1850, 1417, 2057, 1468, 1694,
		  1776, 1456, 1489, 1618, 1544,
		  1251, 1422, 1506, 1651, 1687, 
		  1080, 1866, 1713, 1624, 1370,
		  2107, 1668, 1411, 1654, 1503,
		  1934, 1451, 1240, 1500, 1606 };

main()
{
  size_t N = sizeof( data ) / sizeof(double);
  stddev sd;
  double mu, sigma;
  
  sigma = sd.sd( data, N );
  mu = sd.mean();
  printf("stddev = %7.4f, mean = %7.4f\n", sigma, mu );
}
