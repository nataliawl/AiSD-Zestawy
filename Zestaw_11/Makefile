# Makefile
# Kompilator g++.
CXX = g++

CXXFLAGS = -Wall -std=c++11
OBJECTS = main.o
HFILES = avl_tree.h
TARGET = main.out

%.o : %.cpp $(HFILES) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) 

.PHONY : clean

clean :
	$(RM) $(TARGET) *.o core
