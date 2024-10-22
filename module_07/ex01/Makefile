NAME = iter

CC = c++

GFLAGS = -Wall -Wextra -Werror -Wshadow -Wpedantic -std=c++11

SRCDIR = src/
OBJDIR = obj/

SRCFILES = main.cpp

SRCOBJ = $(SRCFILES:%.cpp=$(OBJDIR)%.o)
DEPS = $(SRCOBJ:.o=.d)

HEADERS = -I include


all: $(NAME)

$(NAME): $(SRCOBJ)
	$(CC) $(GFLAGS) $(SRCOBJ) $(HEADERS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@mkdir -p ${OBJDIR}
	$(CC) $(HEADERS) -MMD -MP -c $(GFLAGS) -o $@ $<

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

-include $(DEPS)
.PHONY: all clean fclean re

