#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

#define CLOSE		"\001\033[0m\002"			// Закрыть все свойства
#define BOLD		"\001\033[1m\002"			// Подчеркнуть, жирным шрифтом, выделить
#define BEGIN(x,y)	"\001\033["#x";"#y"m\002"	// x: background, y: foreground

//int		g_ext_stat;

typedef struct s_shell
{
	char			*input;
	struct s_envl	*env_copy;
}					t_shell;

typedef struct s_envl
{
	char			*line;
	char			*key;
	char			*value;
	struct s_envl	*next;
}					t_envl;

char	*find_in_env(t_envl *env_copy, char *key);
void	change_value_in_env_copy(t_envl *env_copy, char *key, char *value);
void	*allocator(size_t size);
void	liberator(t_shell *mini);

t_envl	*copying_envp(char **envp);
void	envl_lstadd_back(t_envl	**list, t_envl *new);
t_envl	*envl_lstnew(char *env_str);
char	*copy_key(char *env_part);
char	*copy_value(char *env_part);

void	starting(t_shell *mini, t_envl *env_copy);

void	shlvl_up(t_shell *mini);
void	shlvl_down(t_shell *mini);

#endif