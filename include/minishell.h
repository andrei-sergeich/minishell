#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

#define CLOSE		"\001\033[0m\002"			// Закрыть все свойства
#define BLOD		"\001\033[1m\002"			// Подчеркнуть, жирным шрифтом, выделить
#define BEGIN(x,y)	"\001\033["#x";"#y"m\002"	// x: background, y: foreground

int		g_status;

typedef struct s_shell
{
	char			*input;
	struct s_envl	*env_copy;
}					t_shell;

typedef struct s_envl
{
	char			*key;
	char			*value;
//	char			*content;
	struct s_envl	*next;
}					t_envl;

#endif