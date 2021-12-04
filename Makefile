NAME	=	minishell

LIB_DIR	=	libft
SRCS	=	${shell find ./srcs -name "*.c"}
OBJS	=	$(patsubst %.c,%.o,$(SRCS))

HEADER	=	-I./include/

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -lreadline
RM		=	rm -f

all:		$(NAME)

$(NAME):	$(OBJS) include
			@echo "\033[0;32m----Compiling project----\033[0m"
			@make -C $(LIB_DIR)
			@$(CC) $(CFLAGS) $(OBJS) $(LIB_DIR)/libft.a -o $(NAME)
			@#clear
			@echo "Let's go into bash, my Master!!!"

%.o:		%.c
			@$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)

clean:
			@make clean -C $(LIB_DIR)
			$(RM) $(OBJS)

fclean:		clean
			@make fclean -C $(LIB_DIR)
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus