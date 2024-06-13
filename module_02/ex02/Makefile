NAME = fixedNumber
TNAME = tester

CC = c++

GFLAGS = -Wall -Wextra -Werror -Wshadow -std=c++98

SRCDIR = src/
OBJDIR = obj/

SRCFILES = Fixed.cpp main.cpp
SRCOBJ = $(SRCFILES:%.cpp=$(OBJDIR)%.o)

TSRCFILES = Fixed.cpp tester.cpp
TSRCOBJ = $(TSRCFILES:%.cpp=$(OBJDIR)%.o)

HEADERS = -I include

.PHONY: all clean fclean re tester

all: $(NAME)

$(NAME): $(SRCOBJ)
	$(CC) $(GFLAGS) $(SRCOBJ) $(HEADERS) -o $(NAME)

tester: $(TSRCOBJ)
	$(CC) $(TSRCOBJ) $(HEADERS) -o $(TNAME)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@mkdir -p ${OBJDIR}
	$(CC) -c $(GFLAGS) -o $@ $<

$(OBJDIR)%.o: $(TSRCDIR)%.cpp
	@mkdir -p ${OBJDIR}
	$(CC) -c -o $@ $<

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(TNAME)

re: fclean all
