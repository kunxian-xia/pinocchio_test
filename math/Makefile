
all: libMath.a

libMath.a: Field.o SparsePolynomial.o Encoding.o
	ar rcs libMath.a Field.o SparsePolynomial.o Encoding.o
	rm -f *.o


#Field.o: Field.cpp
	#g++ -std=c++11 -g -DVERBOSE -I.. -c Field.cpp

#SparsePolynomial.o: SparsePolynomial.cpp
	#g++ -std=c++11 -g -DVERBOSE -I.. -c SparsePolynomial.cpp

%.o: %.cpp
	g++ -std=c++11 -g -DVERBOSE -DUSE_BN128 -I.. -c $<

clean:
	rm -f *.o
	rm -f libMath.a