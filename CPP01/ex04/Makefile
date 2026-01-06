NAME		= replace
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
SRCS		= main.cpp
OBJS		= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -f *.replace

re: fclean all

.PHONY: all clean fclean re test