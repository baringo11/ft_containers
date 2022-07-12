NAME = ft_containers
CXX = clang++
CXXFLAGS = -Werror -Wall -Wextra -std=c++98 -IVector -IStack -IMap

INCL = 		srcs/utils/reverse_iterator.hpp srcs/utils/lexicographical_compare.hpp 	srcs/utils/equal.hpp\
			srcs/utils/enable_if.hpp srcs/utils/is_integral.hpp srcs/utils/iterator_traits.hpp \
			srcs/Vector/vector.hpp srcs/Vector/vector_iterator.hpp \
			srcs/Stack/stack.hpp \
			srcs/Map/map.hpp srcs/Map/tree_iterator.hpp 

FILES = srcs/main.cpp

OBJ_DIR = obj
FT_OBJS = $(addprefix $(OBJ_DIR)/,$(FILES:.cpp=.o_ft))
STD_OBJS =	$(addprefix $(OBJ_DIR)/,$(FILES:.cpp=.o_std))

TSRCS =		srcs/time_test.cpp
FT_TOBJS =	$(addprefix $(OBJ_DIR)/,${TSRCS:.cpp=.o_ft})
STD_TOBJS =	$(addprefix $(OBJ_DIR)/,${TSRCS:.cpp=.o_std})

RANDINT := ${shell bash -c 'echo $$RANDOM'}

all: $(NAME)

${NAME}:	${NAME}_ft

test:		${NAME}_test_ft

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

${NAME}_test_ft:	${FT_TOBJS} ${STD_TOBJS}
	${CXX} ${CXXFLAGS} -o ${NAME}_test_ft  ${FT_TOBJS}
	${CXX} ${CXXFLAGS} -o ${NAME}_test_std ${STD_TOBJS}
	./${NAME}_test_std ${RANDINT}
	@echo "\n<------------------------------------------------------------------------------------------------------------------------------------>\n"
	./${NAME}_test_ft ${RANDINT}

clean :
	rm -f *.o_ft *.o_std .ft .std
	rm -rf obj

fclean : clean
	rm -f $(NAME)_ft $(NAME)_std $(NAME)_test_ft $(NAME)_test_std

re: fclean all

.PHONY: clean fclean all re