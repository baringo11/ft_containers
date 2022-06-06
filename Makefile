NAME = container
CXX = clang++
CXXFLAGS = -Werror -Wall -Wextra -std=c++98 -IVector

INCL = 		srcs/utils/reverse_iterator.hpp \
			srcs/utils/enable_if.hpp srcs/utils/is_integral.hpp srcs/utils/iterator_traits.hpp \
			srcs/Vector/vector.hpp srcs/Vector/vector_iterator.hpp

FILES = srcs/main.cpp

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(FILES:.cpp=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: %.cpp ${INCL} Makefile
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CXX) -o $@ $(OBJ)

clean :
	rm -f *.o
	rm -rf obj

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re