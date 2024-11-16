CC=clang++
CFLAGS=-g -Wall -std=c++20
DEPS=../Geometry/Point3D.h ../Geometry/PointCloudFactory.h ../Graphs/KDTree.h
SRCS=nearest_neighbor_testing.cpp ../Geometry/PointCloudFactory.cpp ../Graphs/KDTree.cpp
OBJS=$(SRCS:.cpp=.o)
BIN=main

all:$(BIN)

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r main *.o
