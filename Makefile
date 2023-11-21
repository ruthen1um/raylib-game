SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
PROG = game

CXXFLAGS := -Wall
LDFLAGS := -lraylib
CXX := g++

all: clean options $(PROG)

options:
	@echo "build options:"
	@echo "CXXFLAGS = ${CXXFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CXX      = ${CXX}"

$(PROG): $(OBJ) | $(BIN_DIR)
	$(CXX) $^ -o $(BIN_DIR)/$@ $(LDFLAGS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

.PHONY: clean options all
