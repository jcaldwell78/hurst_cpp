
#
# Makefile to build the hursttst(.exe) executable.  This
# tests the rescaled range calculation against a synthetic
# data set.
#
# This is a Microsoft nmake make file (sorry).  To run this
# make file simply enter "nmake" or "nmake -f Makfile".
#
# This Makefile is also the Makefile that generates the
# documentation using doxygen (see www.doxygen.org).  To
# generate HTML documentation from the source code enter
# "nmake doxygen".  The doxygen program uses the doxygenDocConfig
# file.  You will need to install doxygen on your system if you
# don't have it and change the DOXYPATH Makefile variable.
#
# Ian Kaplan
# iank@bearcave.com
# www.bearcave.com
#

DEBUG     = -Zi
BROWSE    = 

CFLAGS    = $(BROWSE) $(DEBUG) -DWIN32 -GX -Tp
OBJ       = obj
EXE       = .exe

DOXYPATH = g:\doxygen\bin

# Include path for Microsoft Visual C++ (this is the 6.0 version)
SYSINC = "c:\Program Files\Microsoft Visual Studio\VC98\Include"

INCLUDE = -I"include" -I"..\stat\include" -I"..\data\include" -I$(SYSINC)

TAR_SRC_LIST = README_HURST hurst stat data freq/include/spectrum.h freq/src/spectrum.cpp histo/include/generic_sort.h histo/include/dbl_sort.h histo/include/histogram.h histo/src/histogram.cpp include/liftbase.h include/daub.h include/line.h include/line_norm.h include/haar.h

STATOBJ = lregress.$(OBJ)

OBJECTS = $(STATOBJ) hurst_base.$(OBJ) rescaled_range.$(OBJ) hursttst.$(OBJ) yahooTS.$(OBJ)

ALL: tests

tests: hursttst$(EXE)

clean:
	rm -f *.obj *.pdb *.sbr *.ilk *.exe 
	rm -f include/*~
	rm -f src/*~

doxygen:
	$(DOXYPATH)\doxygen doxygenDocConfig

tarfile:
	cd ..
	tar cf hurst.tar $(TAR_SRC_LIST)

hursttst$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS) $(DEBUG) -GX -o $*$(EXE)

lregress.$(OBJ): ..\stat\src\$*.cpp ..\stat\include\$*.h
	$(CC) -c $(INCLUDE) $(CFLAGS) ..\stat\src\$*.cpp

yahooTS.$(OBJ): ..\data\src\$*.cpp ..\data\include\$*.h
	$(CC) -c $(INCLUDE) $(CFLAGS) ..\data\src\$*.cpp

hursttst.$(OBJ): *.cpp
	$(CC) -c $(INCLUDE) $(CFLAGS) $*.cpp

rescaled_range.$(OBJ): src\$*.cpp include\$*.h
	$(CC) -c $(INCLUDE) $(CFLAGS) src\$*.cpp

hurst_base.$(OBJ): src\$*.cpp include\$*.h
	$(CC) -c $(INCLUDE) $(CFLAGS) src\$*.cpp
