
#ifndef _SPECTRUM_H_
#define _SPECTRUM_H_

/**
  A collection of functions for spectral analysis
 */
class spectrum {
private:
  /// This class is designed to provide static functions, not
  /// to be declared as a class instance.
  spectrum()  {}
  ~spectrum() {}
  spectrum(const spectrum &rhs) {}
public:
  static void spectralCalc( const double *a, 
			     const size_t N,
			     std::vector<double> &v );

  static void copyBands( double *dest,
			 const double *src,
			 const size_t N,
			 size_t startBand,
			 const size_t endBand );
};

#endif
