NUM_CORES := $(shell grep -c ^processor /proc/cpuinfo)
MAKEFLAGS += --jobs=$(NUM_CORES) --max-load=$(NUM_CORES)

PROG := contagion

BIN_DIR := bin
EXE := $(BIN_DIR)/$(PROG)

SRC_DIR := src
SRC_INT_DIR := $(BIN_DIR)/intermediates/src

TEST_DIR := test
TEST_INT_DIR := $(BIN_DIR)/intermediates/test

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)%,$(SRC_INT_DIR)%,$(SRCS:.cpp=.o))
DEPS := $(patsubst $(SRC_DIR)%,$(SRC_INT_DIR)%,$(SRCS:.cpp=.d))

TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS := $(patsubst $(TEST_DIR)%,$(TEST_INT_DIR)%,$(TEST_SRCS:.cpp=.o))
TEST_DEPS := $(patsubst $(TEST_DIR)%,$(TEST_INT_DIR)%,$(TEST_SRCS:.cpp=.d))

INCLUDE_PATH := -I inc
INCLUDE_PATH += -I vendor

CXX      := g++
CPPFLAGS := --std=c++98 -Wall -Wextra -Werror -g -O0 $(INCLUDE_PATH)
LDFLAGS  :=

QUIET := @

.PHONY: obj test clean

obj: $(OBJS)

test: $(EXE)
	$(QUIET)$(EXE) --use-colour yes --order rand --rng-seed time

$(EXE): $(OBJS) $(TEST_OBJS)
	$(QUIET)echo 'Linking ...'
	$(QUIET)$(CXX) $(LDFLAGS) -o $@ $^

$(SRC_INT_DIR):
	$(QUIET)mkdir -p $(SRC_INT_DIR)

$(SRC_INT_DIR)/%.o: $(SRC_DIR)/%.cpp | $(SRC_INT_DIR)
	$(QUIET)echo 'Compiling $< ...'
	$(QUIET)$(CXX) $(CPPFLAGS) -MMD -c $< -o $@

$(TEST_INT_DIR):
	$(QUIET)mkdir -p $(TEST_INT_DIR)

$(TEST_INT_DIR)/%.o: $(TEST_DIR)/%.cpp | $(TEST_INT_DIR)
	$(QUIET)echo 'Compiling $< ...'
	$(QUIET)$(CXX) $(CPPFLAGS) -MMD -c $< -o $@

-include $(DEPS)
-include $(TEST_DEPS)

clean:
	$(QUIET)echo 'Cleaning ...'
	$(QUIET)rm -rf ./$(BIN_DIR)
