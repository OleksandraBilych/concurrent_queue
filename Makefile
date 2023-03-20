# the compiler
CXX = g++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CPPFLAGS = -g -std=c++11 -pthread -Wall
LD_FLAGS =

main: main.o
	$(CXX) $(CPPFLAGS) -o main main.o ConcurrentQueue.hpp
