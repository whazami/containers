
NAME		= ft
REAL		= std

# My main
SRCS_DIR	= mains/mine/
SRCS		= main_vector.cpp
#SRCS		= main_map.cpp
#SRCS		= main_stack.cpp
#SRCS		= main_rev_it.cpp

OBJS_D		= objs/
OBJS_D_R	= objs_r/
OBJS		= ${SRCS:%.cpp=${OBJS_D}%.o}
OBJS_R		= ${SRCS:%.cpp=${OBJS_D_R}%.o}

# Subject main
SRCS_DIR_S	= mains/
SRCS_S		= subject.cpp

OBJS_DS		= objs/
OBJS_DRS	= objs_r/
OBJS_S		= ${SRCS_S:%.cpp=${OBJS_DS}%.o}
OBJS_RS		= ${SRCS_S:%.cpp=${OBJS_DRS}%.o}

NAME_S		= ft_subject
REAL_S		= std_subject

HEADERS		= containers/vector.hpp \
			  containers/map.hpp \
			  iterators/vector_iterator.hpp \
			  iterators/map_iterator.hpp \
			  utils/AVL.hpp

SEED 		= $(eval SEED := $(shell awk 'BEGIN{srand();print int(rand()*100)}'))$(SEED)

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -pedantic
RM			= rm -f

# My main
${OBJS_D}%.o: ${SRCS_DIR}%.cpp ${HEADERS}
		mkdir -p ${OBJS_D}
		${CXX} ${CXXFLAGS} -D NAMESPACE="ft" -D MINE="1" -c $< -o $@
${OBJS_D_R}%.o: ${SRCS_DIR}%.cpp
		mkdir -p ${OBJS_D_R}
		${CXX} ${CXXFLAGS} -D NAMESPACE="std" -c $< -o $@

# Subject main
${OBJS_DS}%.o: ${SRCS_DIR_S}%.cpp ${HEADERS}
		@mkdir -p ${OBJS_DS}
		@${CXX} ${CXXFLAGS} -D NAMESPACE="ft" -D MINE="1" -c $< -o $@
${OBJS_DRS}%.o: ${SRCS_DIR_S}%.cpp
		@mkdir -p ${OBJS_DRS}
		@${CXX} ${CXXFLAGS} -D NAMESPACE="std" -c $< -o $@

all:	${NAME}

${NAME}:	${OBJS}
			${CXX} ${CXXFLAGS} -o ${NAME} ${OBJS}

${REAL}:	${OBJS_R}
			${CXX} ${CXXFLAGS} -o ${REAL} ${OBJS_R}

test:	
		@echo -n "\033[95mCompiling...\033[0m"
		@make -s ${NAME}
		@make -s ${REAL}
		@mkdir -p logs
		@./${NAME} > logs/ft
		@./${REAL} > logs/std
		@echo "\033[93m\n\n--- DIFF ---\033[0m"
		@diff logs/ft logs/std;\
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

subject: ${OBJS_S} ${OBJS_RS}
		@echo "\e[1 \033[94mSeed:" ${SEED} "\e[0m"
		@echo -n "\033[95mCompiling...\033[0m"
		@${CXX} ${CXXFLAGS} -o ${NAME_S} ${OBJS_S}
		@${CXX} ${CXXFLAGS} -o ${REAL_S} ${OBJS_RS}
		@mkdir -p logs
		@./${NAME_S} ${SEED} > logs/ft
		@./${REAL_S} ${SEED} > logs/std
		@echo "\033[93m\n\n--- DIFF ---\033[0m"
		@diff logs/ft logs/std;\
		EXIT_CODE=$$?;\
		if [ $$EXIT_CODE = 0 ]; then\
			echo "\033[92m  Success!\033[0m";\
		fi;\
		exit 0
		@echo "\033[93m\n--- TIME ---"
		@echo -n "\033[96mstd: "
		@ts=$$(date +%s%N) ; ./${REAL_S} ${SEED} > /dev/null ; tt=$$((($$(date +%s%N) - $$ts)/1000000)) ; echo "$$tt ms"
		@echo -n "\033[92mft: "
		@ts=$$(date +%s%N) ; ./${NAME_S} ${SEED} > /dev/null ; tt=$$((($$(date +%s%N) - $$ts)/1000000)) ; echo "$$tt ms"
		@echo -n "\033[0m"


clean:
		rm -rf ${OBJS_D} ${OBJS_D_R}

fclean:	clean
	   	${RM} ${NAME} ${REAL}
	   	${RM} ${NAME_S} ${REAL_S}
		rm -rf logs

re:		fclean all

.PHONY:	all test subject clean fclean re

