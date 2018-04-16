

all: libqsp.a

libqsp.a:  BoolGate.o BoolCircuit.o  \
		 GateBoolAND.o GateBoolXOR.o GateBoolNAND.o GateBoolOR.o \
		 CircuitBinaryAdder.o QSP.o 
	ar rcs libqsp.a BoolGate.o BoolCircuit.o \
		 GateBoolAND.o GateBoolXOR.o GateBoolNAND.o GateBoolOR.o \
		 CircuitBinaryAdder.o QSP.o
	rm -f *.o

%.o: %.cpp 
	g++ -std=c++11 -g -DVERBOSE -I.. -c $<

clean: *.o 
	rm -f *.o