CXX			:= g++
CXXFLAGS	:= -Wall -O3
SRC_SUFFIX	:= c
SRCS		:= $(patsubst src/%.$(SRC_SUFFIX), %.$(SRC_SUFFIX), $(wildcard src/*.$(SRC_SUFFIX)))
OBJ_DIR		:= obj/
BIN_DIR		:= bin/
VPATH		:= src:${OBJ_DIR}

P2: $(SRCS:.c=.o)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)$@ $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS)) -lm
.PHONY: P2

clean:
	@rm -rf $(BIN_DIR)
	@rm -rf $(OBJ_DIR)
.PHONY: clean

%.o: %.$(SRC_SUFFIX)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $(OBJ_DIR)$@ $<

