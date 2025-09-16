CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O0 -g -fprofile-arcs -ftest-coverage
LDFLAGS = -lgtest -lgtest_main -pthread

SRC = main.cpp
OUT = program.out
OUT_COV = program_coverage.out

all: $(OUT)

coverage: $(OUT_COV)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@ $(LDFLAGS)

$(OUT_COV): $(SRC)
	$(CXX) $(CXXFLAGS) --coverage $(SRC) -o $@ $(LDFLAGS)

clean:
	rm -f $(OUT) $(OUT_COV) *.gcno *.gcda *.gcov coverage.json coverage.cobertura.xml
