NAME		=	test
NAME_D		=	${NAME}_debug

CC			=	clang
FLAGS		=	-Wall -Werror -Wextra
FLAGS_D		=	-g

LINK		=	-lpthread -fsanitize=thread

SRCS		=	$(addprefix srcs/,\
					main.c exit.c time.c fill.c initial.c deinitial.c check.c action.c utilities_int.c utilities_string.c validation.c\
					debug.c)
HEADERS		=	includes/header.h includes/time.h

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
				@$(CC) ${INCLUDES} $(FLAGS_D) $(FLAGS) -c $< -o $@
				@printf "$(COLOR_LCYAN)build object$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
				@printf "ready $(COLOR_LYELLOW)$@$(NOCOLOR)$(NEWLINE)"

.phony		:	all debug clean fclean re run

all			:	$(NAME)

debug		:	${NAME_D}

$(NAME)		:	$(OBJS) $(HEADERS)
				@$(CC) $(LINK) $(OBJS) -L$(LIB_PATH) -l$(LIB_NAME_S) -o $(NAME)
				@printf "$(COLOR_LCYAN)link$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
				@printf "ready $(COLOR_LYELLOW)$(NAME)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"

$(NAME_D)	:	$(OBJS_D) $(HEADERS)
				@$(CC) $(LINK) $(OBJS_D) -L$(LIB_PATH) -l$(LIB_NAME_S_D) -o $(NAME_D)
				@printf "$(COLOR_LCYAN)link debug$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
				@printf "ready $(COLOR_LYELLOW)$(NAME_D)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"

clean		:	
				@$(RM) $(OBJS) $(OBJS_D)
				@printf "$(COLOR_LCYAN)$@$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
				@printf "ready $(COLOR_LYELLOW)$(NAME)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"

fclean		:	clean
				@$(RM) $(NAME) $(NAME_D)
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