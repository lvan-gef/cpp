# for the tester that we can use source
SHELL := /bin/bash

NAME = btc
NAME_DEBUG = $(NAME)_debug

# compiler + default flags
CXX ?= c++
BASE_FLAGS := -std=c++11
WARNING_FLAGS := -Wall -Wextra -Werror -Wshadow -Wconversion -Wdouble-promotion -Wpedantic
CXXFLAGS = $(BASE_FLAGS) $(WARNING_FLAGS)
DEP_FLAGS := -MMD -MP

# build flags
DEBUG_FLAGS := -g3 -DDEBUG
RELEASE_FLAGS := -DNDEBUG

# dirs
SRCDIR = src/
OBJDIR = obj/
TESTDIR = tester/

OBJDIR_RELEASE = $(OBJDIR)release/
OBJDIR_DEBUG = $(OBJDIR)debug/
VENV_DIR := $(TESTDIR).venv

# files
SRCFILES = BitcoinExchange.cpp FileHandler.cpp main.cpp Utils.cpp
SRCS = $(addprefix $(SRCDIR), $(SRCFILES))

# build dirs
OBJS = $(SRCFILES:%.cpp=$(OBJDIR_RELEASE)%.o)
OBJS_DEBUG = $(SRCFILES:%.cpp=$(OBJDIR_DEBUG)%.o)

DEPS = $(OBJS:.o=.d)
DEPS_DEBUG = $(OBJS_DEBUG:.o=.d)

# include all headers
HEADERS = -I include

.PHONY: all
all: $(NAME)

.PHONY: debug
debug: $(NAME_DEBUG)

.PHONY: test
test: $(NAME)
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
	$(VENV_PATH)/bin/python tester/bitcoin_tester.py $(NAME)

.PHONY: fmt
fmt:
	@echo "Format code"
	@find . -type f -name "*.*pp" -print0 | xargs -0 clang-format -i

.PHONY: clean
clean:
	rm -rf $(OBJDIR)

.PHONY: fclean
fclean: clean
	rm -f $(NAME) $(NAME_DEBUG)
	rm -rf $(VENV_DIR) $(TESTDIR)__pycache__

.PHONY: re
re: fclean all

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
