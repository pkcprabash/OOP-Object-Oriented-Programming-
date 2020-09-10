CXXFLAGS += -std=c++11
GTKFLAGS =`/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

ex:  project.o main.o
	$(CXX) $(CXXFLAGS) -o project main.o project.o $(GTKFLAGS)
main.o: project.h main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp $(GTKFLAGS)
project.o: project.h project.cpp 
	$(CXX) $(CXXFLAGS) -c project.cpp $(GTKFLAGS)

