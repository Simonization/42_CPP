NAME		= diamondtrap
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -Wshadow 
#-Wno-shadow

SRCS		= main.cpp \
			  ClapTrap.cpp \
			  ScavTrap.cpp \
			  FragTrap.cpp \
			  DiamondTrap.cpp

OBJS		= $(SRCS:.cpp=.o)

HEADERS		= ClapTrap.hpp \
			  ScavTrap.hpp \
			  FragTrap.hpp \
			  DiamondTrap.hpp

RM			= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o:		%.cpp $(HEADERS)
			$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re