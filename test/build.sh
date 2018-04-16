#!/bin/sh

cd ../math
make 

cd ../qsp
make 

cd ../test
make

./qsp_test.out