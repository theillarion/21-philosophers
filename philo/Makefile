NAME		=	philo
NAME_D		=	${NAME}_debug

CC			=	cc
FLAGS		=	-Wall -Werror -Wextra
FLAGS_D		=	-g

LIB_NAME		=	libqueue.a
LIB_NAME_D		=	libqueue_debug.a
LIB_NAME_S		=	queue
LIB_NAME_S_D	=	queue_debug
LIB_PATH		=	libs/queue/
LIB				=	$(LIB_PATH)$(LIB_NAME)
LIB_D			=	$(LIB_PATH)$(LIB_NAME_D)

LINK		=	-lpthread# -fsanitize=thread
LINK_LIB	=	-l$(LIB_NAME_S) -L$(LIB_PATH)
LINK_LIB_D	=	-l$(LIB_NAME_S_D) -L$(LIB_PATH)

SRCS		=	$(addprefix srcs/,\
					main.c exit.c time.c fill.c initial.c deinitial.c check.c action.c utilities_int.c utilities_string.c validation.c\
					debug.c print.c utilities_queue.c utilities.c)
HEADERS		=	includes/header.h

OBJS		=	${SRCS:%.c=%.o}
OBJS_D		=	${SRCS:%.c=%_debug.o}

INCLUDES	=	-I includes
RM			=	rm -rf

OS				=	${shell uname -s}

NOCOLOR			=	\033[0m
COLOR_LGREEN	=	\033[92m
COLOR_LYELLOW	=	\033[93m
COLOR_LCYAN		=	\033[96m
NEWLINE			=	\n

%.o			:	%.c $(HEADERS)
				@$(CC) ${INCLUDES} $(FLAGS) -c $< -o $@
				@printf "$(COLOR_LCYAN)build object$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
				@printf "ready $(COLOR_LYELLOW)$@$(NOCOLOR)$(NEWLINE)"

%_debug.o	:	%.c $(HEADERS)
				@$(CC) ${INCLUDES} $(FLAGS_D) $(FLAGS) -DDEBUG_MODE -c $< -o $@
				@printf "$(COLOR_LCYAN)build object$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
				@printf "ready $(COLOR_LYELLOW)$@$(NOCOLOR)$(NEWLINE)"

.phony		:	all debug clean fclean re run

all			:	$(NAME)

debug		:	${NAME_D}

$(NAME)		:	$(LIB) $(OBJS)
				@$(CC) $(LINK) $(OBJS) $(LINK_LIB) -o $(NAME)
				@printf "$(COLOR_LCYAN)link$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
				@printf "ready $(COLOR_LYELLOW)$(NAME)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"

$(NAME_D)	:	$(LIB_D) $(OBJS_D)
				@$(CC) $(OBJS_D) $(LINK_LIB_D) -o $(NAME_D)
				@printf "$(COLOR_LCYAN)link debug$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
				@printf "ready $(COLOR_LYELLOW)$(NAME_D)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"

$(LIB)		:
				@$(MAKE) -C $(LIB_PATH)

$(LIB_D)		:
				@$(MAKE) debug -C $(LIB_PATH)

clean		:	
				@$(RM) $(OBJS) $(OBJS_D)
				@$(MAKE) clean -C $(LIB_PATH)
				@printf "$(COLOR_LCYAN)$@$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
				@printf "ready $(COLOR_LYELLOW)$(NAME)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"

fclean		:	clean
				@$(RM) $(NAME) $(NAME_D)
				@$(MAKE) fclean -C $(LIB_PATH)
				@printf "$(COLOR_LCYAN)$@$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
				@printf "ready $(COLOR_LYELLOW)$(NAME)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"

re			:	fclean all
				@printf "$(COLOR_LCYAN)$@$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
				@printf "ready $(COLOR_LYELLOW)$(NAME)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"

run			:	$(NAME_D)
				@printf "$(COLOR_LCYAN)$@$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]$(NEWLINE)"
				@./$(NAME_D)

valgrind	:	$(NAME_D)
				@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME_D)

print-%  	: ; @echo $* = $($*)