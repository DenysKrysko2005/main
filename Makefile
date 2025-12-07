CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

SRC_DIR = src
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/Person.cpp $(SRC_DIR)/FileUtils.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = students

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
