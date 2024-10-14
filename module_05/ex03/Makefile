NAME = bureucrat

CC = c++

GFLAGS = -Wall -Wextra -Werror -Wshadow -Wpedantic -std=c++11

SRCDIR = src/
OBJDIR = obj/

SRCFILES = AForm.cpp Bureaucrat.cpp Intern.cpp main.cpp PresidentialPardonForm.cpp RobotomyRequestForm.cpp ShrubberyCreationForm.cpp

SRCOBJ = $(SRCFILES:%.cpp=$(OBJDIR)%.o)

HEADERS = -I include

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRCOBJ)
	$(CC) -I include $(GFLAGS) $(SRCOBJ) $(HEADERS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@mkdir -p ${OBJDIR}
	$(CC) -I include -c $(GFLAGS) -o $@ $<

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
