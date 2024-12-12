# for the tester that we can use source
SHELL := /bin/bash

NAME := PmergeMe
NAME_DEBUG := $(NAME)_debug
NAME_TEST := $(NAME)_tester.py

# compiler + default flags
CXX := c++
BASE_FLAGS := -std=c++11
WARNING_FLAGS := -Wall -Wextra -Werror -Wshadow -Wconversion -Wdouble-promotion -Wformat=2 -Woverloaded-virtual -Wpedantic
CXXFLAGS := $(BASE_FLAGS) $(WARNING_FLAGS)
DEP_FLAGS := -MMD -MP

# build flags
DEBUG_FLAGS := -g3 -DDEBUG
RELEASE_FLAGS := -DNDEBUG

# dirs
SRCDIR := src/
OBJDIR := obj/
TESTDIR := tester/

OBJDIR_RELEASE := $(OBJDIR)release/
OBJDIR_DEBUG := $(OBJDIR)debug/
VENV_DIR := $(TESTDIR).venv

# files
SRCFILES := main.cpp PmergeMeArray.cpp PmergeMe.cpp PmergeMeDeque.cpp
SRCS := $(addprefix $(SRCDIR), $(SRCFILES))

# build dirs
OBJS := $(SRCFILES:%.cpp=$(OBJDIR_RELEASE)%.o)
OBJS_DEBUG := $(SRCFILES:%.cpp=$(OBJDIR_DEBUG)%.o)

DEPS := $(OBJS:.o=.d)
DEPS_DEBUG := $(OBJS_DEBUG:.o=.d)

# include all headers
HEADERS := -I include

# Colors for help message
BLUE := \033[36m
MARGENTA := \033[35m
NC := \033[0m

.PHONY: all
all: $(NAME)  ## Build the release version (default)

.PHONY: debug
debug: $(NAME_DEBUG)  ## Build the debug version

.PHONY: test
test: $(NAME)  ## Build the release and run tests agains it
	@if [ ! -d "$(VENV_DIR)" ]; then \
		echo "Creating Python virtual environment..."; \
		cd tester && \
		python3 -m venv .venv && \
		source .venv/bin/activate && \
		pip install --upgrade pip && \
		pip install -r requirements.txt && \
		deactivate && \
		cd ..; \
	fi
	$(VENV_PATH)/bin/python $(TESTDIR)$(NAME_TEST) $(NAME)

.PHONY: fmt
fmt:  ## Format code via clang-format
	@echo "Format code"
	@find . -type f -name "*.*pp" -print0 | xargs -0 clang-format -i

.PHONY: clean
clean:  ## Clean object files
	rm -rf $(OBJDIR)

.PHONY: fclean
fclean: clean  ## Clean all side effects
	rm -f $(NAME) $(NAME_DEBUG)
	rm -rf $(VENV_DIR) $(TESTDIR)__pycache__

.PHONY: re  ## Clean all and recompile
re: fclean all

.PHONY: help
help:  ## Get help
	@echo -e 'Usage: make ${BLUE}<target>${NC} ${MARGENTA}<options>${NC}'
	@echo -e 'Available targets:'
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "  ${BLUE}%-15s${NC} %s\n", $$1, $$2}' $(MAKEFILE_LIST)

# compile release
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) $^ $(HEADERS) -o $@

# compile debug
$(NAME_DEBUG): $(OBJS_DEBUG)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $^ $(HEADERS) -o $@

# create object files release
$(OBJDIR_RELEASE)%.o: $(SRCDIR)%.cpp | $(OBJDIR_RELEASE)
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) $(DEP_FLAGS) $(HEADERS) -c $< -o $@

# create object files debug
$(OBJDIR_DEBUG)%.o: $(SRCDIR)%.cpp | $(OBJDIR_DEBUG)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(DEP_FLAGS) $(HEADERS) -c $< -o $@

# create obj and or sub folders
$(OBJDIR_RELEASE) $(OBJDIR_DEBUG):
	mkdir -p $@

-include $(DEPS) $(DEPS_DEBUG)
