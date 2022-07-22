
NAME		= ft_containers
REAL		= real

SRCS_DIR	= mains/mine/
SRCS		= main_vector.cpp
#SRCS		= main_map.cpp
#SRCS		= main_stack.cpp
#SRCS		= main_rev_it.cpp

OBJS_D		= objs/
OBJS_D_R	= objs_r/
OBJS		= ${SRCS:%.cpp=${OBJS_D}%.o}
OBJS_R		= ${SRCS:%.cpp=${OBJS_D_R}%.o}

HEADERS		= containers/vector.hpp \
			  containers/map.hpp \
			  iterators/vector_iterator.hpp \
			  iterators/map_iterator.hpp \
			  utils/AVL.hpp

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -pedantic
RM			= rm -f

${OBJS_D}%.o: ${SRCS_DIR}%.cpp ${HEADERS}
		mkdir -p ${OBJS_D}
		${CXX} ${CXXFLAGS} -D NAMESPACE="ft" -D MINE="1" -c $< -o $@
${OBJS_D_R}%.o: ${SRCS_DIR}%.cpp
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
		@echo "\033[93m\n--- TIME ---"
		@echo -n "\033[96mstd: "
		@ts=$$(date +%s%N) ; ./${REAL} > /dev/null ; tt=$$((($$(date +%s%N) - $$ts)/1000000)) ; echo "$$tt ms"
		@echo -n "\033[92mft: "
		@ts=$$(date +%s%N) ; ./${NAME} > /dev/null ; tt=$$((($$(date +%s%N) - $$ts)/1000000)) ; echo "$$tt ms"
		@echo -n "\033[0m"

clean:
		rm -rf ${OBJS_D} ${OBJS_D_R}

fclean:	clean
	   	${RM} ${NAME} ${REAL}
		rm -rf logs

re:		fclean all

.PHONY:	all test clean fclean re

