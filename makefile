test_disjoint: test_disjoint.o disjoint.o
	g++ test_disjoint disjoint.o -o test_disjoint

test_disjoint.o: test_disjoint.cc disjoint.h disjoint.cc
	g++ -c test_disjoint.cc

disjoint.o: disjoint.cc disjoint.h
	g++ -c disjoint.h	

test_graph: graph.o test_graph.o
	g++ graph.o test_graph.o -o test_graph

test_graph.o: test_graph.cc graph.h graph.cc
	g++ -c test_graph.cc

graph.o: graph.cc graph.h
	g++ -c graph.cc

stars: stars.cc
	g++ stars.cc -o stars

coast: coast.cc
	g++ coast.cc -o coast

clean:
	rm *.o
