
#include "wave_hurst.h"

int
main()
{
  const char *path = "..\\data\\equities\\";
  wave_hurst t( path );
  t.test();
  return 0;
}
