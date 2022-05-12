
NAME	= ft_containers

SRCS	= main.cpp

OBJS_D	= objs/
OBJS_D_R= objs_r/
OBJS	= ${SRCS:%.cpp=${OBJS_D}%.o}
OBJS_R	= ${SRCS:%.cpp=${OBJS_D_R}%.o}

CXX		= c++ #-g3 -fsanitize=address
CXXFLAGS= -Wall -Wextra -Werror -std=c++98 -pedantic
RM		= rm -f

${OBJS_D}%.o: %.cpp
		mkdir -p ${OBJS_D}
		${CXX} ${CXXFLAGS} -D NAMESPACE="ft" -c $< -o $@
${OBJS_D_R}%.o: %.cpp
		mkdir -p ${OBJS_D_R}
		${CXX} ${CXXFLAGS} -D NAMESPACE="std" -c $< -o $@

all:	${NAME}

${NAME}:	${OBJS}
			${CXX} ${CXXFLAGS} -o ${NAME} ${OBJS}

real:		${OBJS_R}
			${CXX} ${CXXFLAGS} -o std_containers ${OBJS_R}

test:	
		@echo "\033[95mCompiling...\033[0m"
		@make -s ${NAME}
		@make -s real
		@mkdir -p logs
		@./ft_containers > logs/mine
		@./std_containers > logs/real
		@echo "\033[93m\n--- DIFF ---\033[0m"
		@-diff logs/mine logs/real || true

clean:
		rm -rf ${OBJS_D} ${OBJS_D_R}

fclean:	clean
	   	${RM} ${NAME} std_containers
		rm -rf logs

re:		fclean all

.PHONY:	all real test clean fclean re

