CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2

EIGEN_INCLUDE = /opt/homebrew/include/eigen3

ifeq ($(wildcard $(EIGEN_INCLUDE)/Eigen/Dense),)
	EIGEN_INCLUDE = /usr/local/include/eigen3
endif

ifeq ($(wildcard $(EIGEN_INCLUDE)/Eigen/Dense),)
	EIGEN_INCLUDE = /usr/include/eigen3
endif

all: Gauss_main Gauss_test

Gauss_main: Gauss_main.cpp Gauss_solve.cpp util.cpp Gauss_solve.h util.h
	$(CXX) $(CXXFLAGS) -I$(EIGEN_INCLUDE) Gauss_main.cpp Gauss_solve.cpp util.cpp -o Gauss_main

Gauss_test: Gauss_test.cpp Gauss_solve.cpp util.cpp Gauss_solve.h util.h
	$(CXX) $(CXXFLAGS) -I$(EIGEN_INCLUDE) Gauss_test.cpp Gauss_solve.cpp util.cpp -o Gauss_test

test: all
	./Gauss_test

demo: all
	./Gauss_main AB.csv

clean:
	rm -f Gauss_main Gauss_test result.csv

.PHONY: all test demo clean
