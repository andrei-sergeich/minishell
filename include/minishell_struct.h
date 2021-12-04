#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

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