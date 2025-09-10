NAME		= abstract
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
SRCS		= main.cpp \
			  AAnimal.cpp \
			  Dog.cpp \
			  Cat.cpp \
			  Brain.cpp
OBJS		= $(SRCS:.cpp=.o)
HEADERS		= AAnimal.hpp \
			  Dog.hpp \
			  Cat.hpp \
			  Brain.hpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

leak: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re