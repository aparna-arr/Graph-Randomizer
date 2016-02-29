CXX := g++
CXXFLAGS := -Wall -g
OBJECTS := Main.o UserOpts.o Graph.o

graphmaker: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

Main.o: Main.cpp Main.h UserOpts.h Graph.h
	$(CXX) $(CXXFLAGS) -c Main.cpp

UserOpts.o: UserOpts.cpp UserOpts.h
	$(CXX) $(CXXFLAGS) -c UserOpts.cpp

Graph.o: Graph.cpp Graph.h
	$(CXX) $(CXXFLAGS) -c Graph.cpp


clean:
	rm -f $(OBJECTS) graphmaker
