NAME = mutantStack
TESTNAME = test
BUILD_MODE = build

CC = c++

GFLAGS = -Wall -Wextra -Werror -Wshadow -Wpedantic -std=c++11 -g3

SRCDIR = src/
TESTDIR = tester/src/
OBJDIR = obj/

SRCFILES = main.cpp
# TESTFILES = $(NAME)_test.cpp
TESTFILES = basic_test.cpp complex_type_test.cpp mutantStack_test.cpp subject_test.cpp

SRCOBJ = $(SRCFILES:%.cpp=$(OBJDIR)%.o)
TESTOBJ = $(TESTFILES:%.cpp=$(OBJDIR)%.o)
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
	@if [ "$(BUILD_MODE)" = "build" ]; then \
		if [ "$<" = "$(SRCDIR)main.cpp" ]; then \
			./tester/swap_test.sh build; \
		fi \
	fi

	@mkdir -p ${OBJDIR}
	$(CC) $(GFLAGS) $(HEADERS) -MMD -MP -c -o $@ $<

run: all
	./$(NAME)

test: BUILD_MODE = test
$(TESTNAME): clean $(TESTOBJ) $(SRCOBJ)
	$(CC) $(GFLAGS) -MMD -MP $(SRCOBJ) $(TESTOBJ) $(HEADERS) -I tester/include -o $(TESTNAME)
	@rm -rf $(OBJDIR)
	@$(CLEAR_COMMAND)
	## valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
	./$(TESTNAME)

$(OBJDIR)%.o: $(TESTDIR)%.cpp
	@if [ "$<" = "$(TESTDIR)$(NAME)_test.cpp" ]; then \
		./tester/swap_test.sh test; \
	fi

	@mkdir -p ${OBJDIR}
	$(CC) $(HEADERS) -MMD -MP -c $(GFLAGS) -I tester/include -o $@ $<

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(TESTNAME)

re: fclean all

-include $(DEPS)
.PHONY: all clean fclean re test run
