# Makefile
# Kompilator g++.
CXX = g++

# Flagi dla kompilatora C++.
# Standardy: -std=c++11 -std=c++14 -std=c++17 -std=c++20 -std=c++23 -std=c++26
CXXFLAGS = -Wall -std=c++11
# Pliki obiektowe - powstają z plików *.cpp.
OBJECTS = main.o 
# Pliki nagłówkowe - są włączane do plików *.cpp.
HFILES = doublelist.h
# Końcowy plik wykonywalny.
TARGET = main.out

# Definicja domyślnej reguły wzorcowej.
# $< oznacza nazwę pliku pierwszej zależności reguły.
# $@ oznacza nazwę pliku celu w regule.
# Wszystkie pliki obiektowe zależą od wszystkich plików nagłówkowych.
# Wcięcia robimy przez TAB.
%.o : %.cpp $(HFILES) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Na końcu wstawiamy $(LIBS), aby nie było problemów z linkowaniem.
$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) 

# Określenie celów sztucznych.
.PHONY : clean

clean :
	$(RM) $(TARGET) *.o core

