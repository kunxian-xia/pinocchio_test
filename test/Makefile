encoding_test: encoding_test.cpp
	g++ -std=c++11 -g -DBN_SUPPORT_SNARK -DUSE_BN128 -I.. -L../math -o encoding_test.out encoding_test.cpp -lMath -lgmp -lff -lzm
qsp_test: qsp_test.cpp 
	g++ -std=c++11 -g -I.. -L../math -L../qsp -o qsp_test.out qsp_test.cpp -lMath -lqsp -lgmp -lff 