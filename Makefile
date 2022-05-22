NAME		=	test
NAME_D		=	${NAME}_debug

CC			=	clang
FLAGS		=	-Wall -Werror -Wextra
FLAGS_D		=	-g

LINK		=	-fsanitize=thread -lpthread

SRCS		=	$(addprefix srcs/,\
					main.c time.c initial.c check.c action.c)
HEADERS		=	includes/header.h includes/time.h

LIB_NAME	=	libvector.a
LIB_NAME_D	=	libvector_debug.a
LIB_NAME_S	=	vector
LIB_NAME_S_D	=	vector_debug
LIB_PATH		=	libs/vector/

LIB_VECTOR		=	$(LIB_PATH)$(LIB_NAME)
LIB_VECTOR_D	=	$(LIB_PATH)$(LIB_NAME_D)

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

$(NAME)		:	$(LIB_VECTOR) $(OBJS) $(HEADERS)
				@$(CC) $(LINK) $(OBJS) -L$(LIB_PATH) -l$(LIB_NAME_S) -o $(NAME)
				@printf "$(COLOR_LCYAN)link$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
				@printf "ready $(COLOR_LYELLOW)$(NAME)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"

$(NAME_D)	:	$(LIB_VECTOR_D) $(OBJS_D) $(HEADERS)
				@$(CC) $(LINK) $(OBJS_D) -L$(LIB_PATH) -l$(LIB_NAME_S_D) -o $(NAME_D)
				@printf "$(COLOR_LCYAN)link debug$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
				@printf "ready $(COLOR_LYELLOW)$(NAME_D)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"

$(LIB_VECTOR)	:
					@printf "$(COLOR_LCYAN)build $(LIB_NAME)$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
					@printf "cd $(COLOR_LYELLOW)$(LIB_PATH)$(NOCOLOR)$(NEWLINE)"
					@$(MAKE) -s -C $(LIB_PATH)
					@printf "$(COLOR_LCYAN)build $(LIB_NAME)$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
					@printf "cd $(COLOR_LYELLOW).$(NOCOLOR)$(NEWLINE)"
					@printf "$(COLOR_LCYAN)build $(LIB_NAME)$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
					@printf "ready $(COLOR_LYELLOW)$(LIB_NAME)$(NOCOLOR)$(NEWLINE)"

$(LIB_VECTOR_D)	:
					@$(MAKE) -s debug -C $(LIB_PATH)
					@printf "$(COLOR_LCYAN)build $(LIB_NAME_D)$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
					@printf "ready $(COLOR_LYELLOW)$(LIB_NAME_D)$(NOCOLOR)$(NEWLINE)"


clean		:	
				@$(RM) $(OBJS) $(OBJS_D)
				@$(MAKE) -s clean -C $(LIB_PATH)
				@printf "$(COLOR_LCYAN)$@$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
				@printf "ready $(COLOR_LYELLOW)$(NAME)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"

fclean		:	clean
				@$(RM) $(NAME) $(NAME_D)
				@$(MAKE) -s fclean -C $(LIB_PATH)
				@printf "$(COLOR_LCYAN)$@$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
				@printf "ready $(COLOR_LYELLOW)$(NAME)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"

re			:	fclean all
				@printf "$(COLOR_LCYAN)$@$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
				@printf "ready $(COLOR_LYELLOW)$(NAME)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"

run			:	$(NAME_D)
				@printf "$(COLOR_LCYAN)$@$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]$(NEWLINE)"
				@./$(NAME_D)

print-%  	: ; @echo $* = $($*)