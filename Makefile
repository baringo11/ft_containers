NAME = ft_container
CXX = clang++
CXXFLAGS = -Werror -Wall -Wextra -std=c++98 -IVector -IStack -IMap

INCL = 		srcs/utils/reverse_iterator.hpp srcs/utils/lexicographical_compare.hpp 	srcs/utils/equal.hpp\
			srcs/utils/enable_if.hpp srcs/utils/is_integral.hpp srcs/utils/iterator_traits.hpp \
			srcs/Vector/vector.hpp srcs/Vector/vector_iterator.hpp \
			srcs/Stack/stack.hpp \
			srcs/Map/map.hpp

FILES = srcs/main.cpp
FT_OBJS = $(addprefix $(OBJ_DIR)/,$(FILES:.cpp=.o_ft))
STD_OBJS =	$(addprefix $(OBJ_DIR)/,$(FILES:.cpp=.o_std))

OBJ_DIR = obj

all: $(NAME)

${NAME}:	${NAME}_ft

$(OBJ_DIR)/%.o_ft:	%.cpp ${INCL} Makefile
		@mkdir -p $(@D)
		$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o_std:	%.cpp ${INCL} Makefile
			@mkdir -p $(@D)
			$(CXX) $(CXXFLAGS) -DNS=std -c $< -o $@

$(NAME)_ft: 	$(FT_OBJS) $(STD_OBJS)
	${CXX} ${CXXFLAGS} -o ${NAME}_ft  ${FT_OBJS}
	${CXX} ${CXXFLAGS} -o ${NAME}_std  $(STD_OBJS)
	./${NAME}_ft  > .ft
	./${NAME}_std > .std

clean :
	rm -f *.o_ft *.o_std .ft .std
	rm -rf obj

fclean : clean
	rm -f $(NAME)_ft $(NAME)_std

re: fclean all

.PHONY: clean fclean all re