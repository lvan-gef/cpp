NAME = serializer

CC = c++

GFLAGS = -Wall -Wextra -Werror -Wshadow -Wpedantic -std=c++11

SRCDIR = src/
OBJDIR = obj/

SRCFILES = main.cpp Serializer.cpp Tester.cpp

SRCOBJ = $(SRCFILES:%.cpp=$(OBJDIR)%.o)

HEADERS = -I include

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRCOBJ)
	$(CC) $(GFLAGS) $(SRCOBJ) $(HEADERS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@mkdir -p ${OBJDIR}
	$(CC) $(HEADERS) -c $(GFLAGS) -o $@ $<

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
