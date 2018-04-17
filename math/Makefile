
all: libMath.a

libMath.a: Field.o SparsePolynomial.o
	ar rcs libMath.a Field.o SparsePolynomial.o
	rm -f *.o

Field.o: Field.cpp
	g++ -std=c++11 -g -DVERBOSE -I.. -c Field.cpp

SparsePolynomial.o: SparsePolynomial.cpp
	g++ -std=c++11 -g -DVERBOSE -I.. -c SparsePolynomial.cpp
#*.o: *.cpp
	#g++ -std=c++11 -g -DVERBOSE -I.. -c $<
clean:
	rm -f *.o
	rm -f libMath.a