# Makefile

CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Isrc

SRC = main.cpp $(wildcard src/*.cpp)
OUT = main # Linux
# OUT = main.exe # Windows
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

clear:
	rm -f $(OUT)