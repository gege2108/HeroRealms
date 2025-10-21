CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++17
INCLUDES=-Iinclude

SRCDIR=src
SRCS=$(wildcard $(SRCDIR)/*.cpp)
OBJS=$(patsubst $(SRCDIR)/%.cpp,%.o,$(SRCS))
TARGET=herorealms

%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

.PHONY: all run clean

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) *~ *.core
