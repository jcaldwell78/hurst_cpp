
#
# Build a test for linear regression and standard 
# deviation.
#
# This is a Microsoft nmake Makefile.  To execute enter "nmake".
# This Makefile will also remove object and debug files built
# by the Microsoft tools ("nmake clean").  Doxygen generated
# Documentation can be created by entering "nmake doxygen".
#

DEBUG     = -Zi
BROWSE    = 

CFLAGS    = $(BROWSE) $(DEBUG) -DWIN32 -Tp
OBJ       = obj
EXE       = .exe

DOXYPATH = g:\doxygen\bin

SYSINC = "c:\Program Files\Microsoft Visual Studio\Vc98\Include"

INCLUDE = -I"include" -I$(SYSINC)

ALL: tests

tests: lrtest$(EXE) sdtest$(EXE)

clean:
	rm -f *.obj *.pdb *.sbr *.ilk *.exe 
	rm -f include/*~
	rm -f src/*~

doxygen:
	$(DOXYPATH)\doxygen doxygenDocConfig

lrtest$(EXE): lrtest.$(OBJ) lregress.$(OBJ)
	$(CC) lrtest.$(OBJ) lregress.$(OBJ) $(DEBUG) -GX -o lrtest$(EXE)

sdtest$(EXE): sdtest.$(OBJ) stddev.$(OBJ)
	$(CC) sdtest.$(OBJ) stddev.$(OBJ) $(DEBUG) -GX -o sdtest$(EXE)

lregress.$(OBJ): src\$*.cpp include\$*.h
	$(CC) -c $(INCLUDE) -GX $(CFLAGS) src\$*.cpp

stddev.$(OBJ): src\$*.cpp include\$*.h
	$(CC) -c $(INCLUDE) $(CFLAGS) src\$*.cpp

lrtest.$(OBJ): $*.cpp 
	$(CC) -c $(INCLUDE) -GX $(CFLAGS) $*.cpp

sdtest.$(OBJ): $*.cpp 
	$(CC) -c $(INCLUDE) $(CFLAGS) $*.cpp
