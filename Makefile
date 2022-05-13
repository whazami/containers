
NAME		= ft_containers
REAL		= real

SRCS		= main.cpp

OBJS_D		= objs/
OBJS_D_R	= objs_r/
OBJS		= ${SRCS:%.cpp=${OBJS_D}%.o}
OBJS_R		= ${SRCS:%.cpp=${OBJS_D_R}%.o}

HEADERS		= vector/vector.hpp \
			  iterators/vector_iterator.hpp

CXX			= c++ #-g3 -fsanitize=address
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -pedantic
RM			= rm -f

${OBJS_D}%.o: %.cpp ${HEADERS}
		mkdir -p ${OBJS_D}
		${CXX} ${CXXFLAGS} -D NAMESPACE="ft" -c $< -o $@
${OBJS_D_R}%.o: %.cpp ${HEADERS}
		mkdir -p ${OBJS_D_R}
		${CXX} ${CXXFLAGS} -D NAMESPACE="std" -c $< -o $@

all:	${NAME}

${NAME}:	${OBJS}
			${CXX} ${CXXFLAGS} -o ${NAME} ${OBJS}

${REAL}:	${OBJS_R}
			${CXX} ${CXXFLAGS} -o ${REAL} ${OBJS_R}

test:	
		@echo -n "\033[95mCompiling...\033[0m"
		@make -s ${NAME}
		@make -s real
		@mkdir -p logs
		@./${NAME} > logs/mine
		@./${REAL} > logs/real
		@echo "\033[93m\n\n--- DIFF ---\033[0m"
		@diff logs/mine logs/real;\
		EXIT_CODE=$$?;\
		if [ $$EXIT_CODE = 0 ]; then\
			echo "\033[92m  Success!\033[0m";\
		fi;\
		exit 0

clean:
		rm -rf ${OBJS_D} ${OBJS_D_R}

fclean:	clean
	   	${RM} ${NAME} ${REAL}
		rm -rf logs

re:		fclean all

.PHONY:	all test clean fclean re

