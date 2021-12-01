NAME	=	minishell

SRCS	=	${shell find ./src -name "*.c"}
OBJS_DIR	=	obj
OBJS	=	$(patsubst %.c,%.o,$(SRCS))

HEADER	=	-I./inc/

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -lreadline
RM		=	rm -f

all:		$(NAME)

$(NAME):	$(OBJS) ./inc/minishell.h
			@echo "\033[33;1m----Compiling project----\033[0m"
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@#clear
			@echo "Let's go into bash, my Master!!!"

%.o:		%.c
			@$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus