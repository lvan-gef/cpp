NAME = scalarConverter

CC = c++

GFLAGS = -Wall -Wextra -Werror -Wshadow -Wpedantic -std=c++11

SRCDIR = src/
OBJDIR = obj/

SRCFILES = main.cpp ScalarConverter.cpp Tester.cpp

SRCOBJ = $(SRCFILES:%.cpp=$(OBJDIR)%.o)

HEADERS = -I include

.PHONY: all clean fclean re tester

all: $(NAME)

$(NAME): $(SRCOBJ)
	$(CC) -I include $(GFLAGS) $(SRCOBJ) $(HEADERS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@mkdir -p ${OBJDIR}
	$(CC) -I include -c $(GFLAGS) -o $@ $<

tester: $(NAME)
	python scaler_tester.py

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
