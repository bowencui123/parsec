CXX ?= g++
CXXFLAGS ?= -O2 -std=c++11
LDFLAGS ?=
LIBS ?= -lm

SRCS = annealer_thread.cpp rng.cpp netlist.cpp netlist_elem.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = canneal

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

