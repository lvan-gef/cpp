NAME = megaphone

CC = c++

FLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = src/
OBJDIR = obj/

SRCFILES = megaphone.cpp
SRCOBJ = $(SRCFILES:%.c=$(OBJDIR)%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRCOBJ)
	$(CC) $(GFLAGS) $(SRCOBJ) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p ${OBJDIR}
	$(CC) -c $(GFLAGS) -o $@ $<

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(B_NAME)

re: fclean all


