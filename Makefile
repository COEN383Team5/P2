CXX			:= gcc
CXXFLAGS	:= -Wall -O3
SRCS		:= $(patsubst src/%.c, %.c, $(wildcard src/*.c))
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

%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $(OBJ_DIR)$@ $<

