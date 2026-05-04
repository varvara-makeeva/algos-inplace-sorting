CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

all: sort_demo sort_test

sort_demo: sort_demo.cpp sorting.h
	$(CXX) $(CXXFLAGS) sort_demo.cpp -o sort_demo

sort_test: sort_test.cpp sorting.h
	$(CXX) $(CXXFLAGS) sort_test.cpp -o sort_test

run: sort_demo
	./sort_demo

test: sort_test
	./sort_test

clean:
	rm -f sort_demo sort_test
