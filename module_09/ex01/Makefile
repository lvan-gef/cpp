NAME = RPN
TESTNAME = test
BUILD_MODE = build

CC = c++

GFLAGS = -Wall -Wextra -Werror -Wshadow -Wpedantic -std=c++11 -g3

SRCDIR = src/
TESTDIR = tester/src/
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
	./$(NAME)

test: BUILD_MODE = test
$(TESTNAME): clean $(TESTOBJ) $(SRCOBJ)
	$(CC) $(GFLAGS) -MMD -MP $(SRCOBJ) $(TESTOBJ) $(HEADERS) -g3 -I tester/include -o $(TESTNAME)
	@rm -rf $(OBJDIR)
	@$(CLEAR_COMMAND)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --read-var-info=yes --track-fds=yes --trace-children=yes ./$(TESTNAME)

$(OBJDIR)%.o: $(TESTDIR)%.cpp
	@mkdir -p ${OBJDIR}
	$(CC) $(HEADERS) -MMD -MP -c $(GFLAGS) -g3 -I tester/include -o $@ $<

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	# @./tester/swap_test.sh build;
	@rm -f $(NAME)
	@rm -f $(TESTNAME)

re: fclean all

fmt:
	@echo "Format code"
	@find . -type f -name "*.*pp" -print0 | xargs -0 clang-format -i

-include $(DEPS)
.PHONY: all clean fclean re test run fmt
