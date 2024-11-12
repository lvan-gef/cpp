SHELL := /bin/bash

NAME = RPN
VENV_PATH="tester/.venv"

CC = c++

GFLAGS = -Wall -Wextra -Werror -Wshadow -Wpedantic -std=c++11

SRCDIR = src/
OBJDIR = obj/

SRCFILES = main.cpp RPN.cpp

SRCOBJ = $(SRCFILES:%.cpp=$(OBJDIR)%.o)
DEPS = $(SRCOBJ:.o=.d)

HEADERS = -I include

ifeq ($(OS),Windows_NT)
    CLEAR_COMMAND = cls
else
    CLEAR_COMMAND = clear
endif

all: $(NAME)

$(NAME): $(SRCOBJ)
	$(CC) $(GFLAGS) $(SRCOBJ) $(HEADERS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@mkdir -p ${OBJDIR}
	$(CC) $(GFLAGS) $(HEADERS) -MMD -MP -c -o $@ $<

run: all
	@$(CLEAR_COMMAND)
	./$(NAME) db/input.txt

test: GFLAGS += -g3
test: all
	@if [ ! -d "$VENV_PATH" ]; then \
		cd tester; \
		python3 -m venv .venv; \
		source .venv/bin/activate; \
		pip install -r requirements.txt; \
		deactivate; \
		cd ..; \
	fi

	@$(CLEAR_COMMAND)
	$(VENV_PATH)/bin/python tester/rpn_tester.py $(NAME)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(TESTNAME)
	@rm -rf $(VENV_PATH)

re: fclean all

fmt:
	@echo "Format code"
	@find . -type f -name "*.*pp" -print0 | xargs -0 clang-format -i

-include $(DEPS)
.PHONY: all clean fclean re test run fmt

