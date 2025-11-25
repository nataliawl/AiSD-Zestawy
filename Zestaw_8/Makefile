# Makefile
# Kompilator g++.
CXX = g++

# Flagi dla kompilatora C++.
# Standardy: -std=c++11 -std=c++14 -std=c++17 -std=c++20 -std=c++23 -std=c++26
CXXFLAGS = -Wall -std=c++11
# Pliki obiektowe - powstaj� z plik�w *.cpp.
OBJECTS = main.o 
# Pliki nag��wkowe - s� w��czane do plik�w *.cpp.
HFILES = queue.h
# Ko�cowy plik wykonywalny.
TARGET = main.out

# Definicja domy�lnej regu�y wzorcowej.
# $< oznacza nazw� pliku pierwszej zale�no�ci regu�y.
# $@ oznacza nazw� pliku celu w regule.
# Wszystkie pliki obiektowe zale�� od wszystkich plik�w nag��wkowych.
# Wci�cia robimy przez TAB.
%.o : %.cpp $(HFILES) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Na ko�cu wstawiamy $(LIBS), aby nie by�o problem�w z linkowaniem.
$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) 

# Okre�lenie cel�w sztucznych.
.PHONY : clean

clean :
	$(RM) $(TARGET) *.o core
