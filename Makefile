NAME		=	ft_containers

HEADER		=	./containers/map.hpp \
				./containers/stack.hpp \
				./containers/vector.hpp \
				./containers/RBTree.hpp
SRC			=	./tests/main.cpp

CC= clang++ -std=c++98
FLAGS = -Wall -Werror -Wextra
OBJ = $(SRC:.cpp=.o)
RM = rm -f

all: $(NAME)

%.o : %.cpp $(HEADER) Makefile
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: all
	./ft_containers

.PHONY: all clean fclean re 