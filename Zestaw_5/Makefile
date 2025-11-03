# Makefile
# Kompilator g++.
CXX = g++

# Flagi dla kompilatora C++.
# Standardy: -std=c++11 -std=c++14 -std=c++17 -std=c++20 -std=c++23 -std=c++26
CXXFLAGS = -Wall -std=c++11
# Pliki obiektowe - powstaj¹ z plików *.cpp.
OBJECTS = main.o 
# Pliki nag³ówkowe - s¹ w³¹czane do plików *.cpp.
HFILES = singlelist.h
# Koñcowy plik wykonywalny.
TARGET = main.out

# Definicja domyœlnej regu³y wzorcowej.
# $< oznacza nazwê pliku pierwszej zale¿noœci regu³y.
# $@ oznacza nazwê pliku celu w regule.
# Wszystkie pliki obiektowe zale¿¹ od wszystkich plików nag³ówkowych.
# Wciêcia robimy przez TAB.
%.o : %.cpp $(HFILES) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Na koñcu wstawiamy $(LIBS), aby nie by³o problemów z linkowaniem.
$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) 

# Okreœlenie celów sztucznych.
.PHONY : clean

clean :
	$(RM) $(TARGET) *.o core
