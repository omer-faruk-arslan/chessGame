CXX = g++ -std=c++17  
CXXFLAGS = -O2 -Wall 
CXXDEBUG = -g -O0
SRC = ./src/*.cpp
TARGET = ./bin/runner

all: $(TARGET)


$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

debug: $(SRC)
	$(CXX) $(CXXDEBUG) $(SRC) -o $(TARGET)


run: $(TARGET)
	$(TARGET)
  
clean: 
	rm -f $(TARGET)