all: undirectedGraphdriver

undirectedGraphdriver: List.cpp List.hpp Map.cpp Map.hpp PriorityQueue.cpp PriorityQueue.hpp undirectedGraph.cpp undirectedGraph.hpp undirectedGraphtest.cpp
		g++ -std=c++11 -o undirectedGraphdriver undirectedGraphtest.cpp List.cpp Map.cpp PriorityQueue.cpp undirectedGraph.cpp

run:    undirectedGraphdriver
	./undirectedGraphdriver < test01.in > out01.out
	./undirectedGraphdriver < test02.in > out02.out
	./undirectedGraphdriver < test03.in > out03.out
	./undirectedGraphdriver < mytest04.in > mytest04.out
	./undirectedGraphdriver < mytest05.in > mytest05.out
	./undirectedGraphdriver < mytest06.in > mytest06.out
	./undirectedGraphdriver < mytest07.in > mytest07.out
	./undirectedGraphdriver < mytest08.in > mytest08.out
	./undirectedGraphdriver < mytest09.in > mytest09.out
