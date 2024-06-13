NAME = animal
TESTNAME = test
BUILD_MODE = build

CC = c++

GFLAGS = -Wall -Wextra -Werror -Wshadow -Wpedantic -std=c++11

SRCDIR = src/
TESTDIR = tester/src/
OBJDIR = obj/

SRCFILES = Animal.cpp Cat.cpp Dog.cpp main.cpp WrongAnimal.cpp WrongCat.cpp
TESTFILES = animal_tester.cpp cat_tester.cpp dog_tester.cpp wronganimal_tester.cpp wrongcat_tester.cpp utils.cpp

SRCOBJ = $(SRCFILES:%.cpp=$(OBJDIR)%.o)
TESTOBJ = $(TESTFILES:%.cpp=$(OBJDIR)%.o)

HEADERS = -I include

.PHONY: all clean fclean re test


all: $(NAME)

$(NAME): $(SRCOBJ)
	$(CC) $(GFLAGS) $(SRCOBJ) $(HEADERS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@if [ "$(BUILD_MODE)" = "build" ]; then \
		if [ "$<" = "$(SRCDIR)main.cpp" ]; then \
			./tester/swap_main.sh build; \
		fi \
	fi

	@mkdir -p ${OBJDIR}
	$(CC) -c $(GFLAGS) -o $@ $<

# test build
test: BUILD_MODE = test

$(TESTNAME): clean $(TESTOBJ) $(SRCOBJ)
	$(CC) $(GFLAGS) $(SRCOBJ) $(TESTOBJ) $(HEADERS) -I tester/include -o $(TESTNAME)
	@rm -rf $(OBJDIR)

$(OBJDIR)%.o: $(TESTDIR)%.cpp
	@if [ "$<" = "$(TESTDIR)animal_tester.cpp" ]; then \
		./tester/swap_main.sh test; \
	fi

	@mkdir -p ${OBJDIR}
	$(CC) -c $(GFLAGS) -o $@ $<

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(TESTNAME)

re: fclean all
