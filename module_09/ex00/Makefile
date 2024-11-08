SHELL := /bin/bash

NAME = btc
VENV_PATH="tester/.venv"

CC = c++

GFLAGS = -Wall -Wextra -Werror -Wshadow -Wpedantic -std=c++11 -g3

SRCDIR = src/
OBJDIR = obj/

SRCFILES = BitcoinExchange.cpp FileHandler.cpp main.cpp Utils.cpp

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
	tester/.venv/bin/python tester/bitcoin_tester.py $(NAME)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(TESTNAME)

re: fclean all

fmt:
	@echo "Format code"
	@find . -type f -name "*.*pp" -print0 | xargs -0 clang-format -i

-include $(DEPS)
.PHONY: all clean fclean re test run fmt
