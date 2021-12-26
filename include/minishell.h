#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
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
	struct s_arg	*args;
}					t_shell;

typedef struct s_envl
{
	char			*line; // maybe delete
	char			*key;
	char			*value;
	struct s_envl	*next;
}					t_envl;

typedef struct s_arg
{
//	char			*arg_as_is;
	char			*arg_cleaned;
	int				redirect;
	struct s_arg	*next;
}				t_arg;

/*
 * utils
 */
void	*allocator(size_t size);
void	liberator(t_shell *mini);
void	envl_destroy(t_envl **lst);
void	envl_lstdelone(t_envl *lst);
int		print_msg(int ret_val, char *message, int ext_stat);

/*
 * copying envp
 */
t_envl	*copying_envp(char **envp);
void	envl_lstadd_back(t_envl	**list, t_envl *new);
t_envl	*envl_lstnew(char *env_str);
char	*copy_key(char *env_part);
char	*copy_value(char *env_part);

/*
 * change value in env copy
 */
void	change_value_in_env_copy(t_envl *env_copy, char *key, char *value);
char	*find_in_env(t_envl *env_copy, char *key);

/*
 * change SHELL LEVEL
 */
void	shlvl_up(t_shell *mini);
void	shlvl_down(t_shell *mini);

/*
 * parsing
 */
void	parsing(t_shell *mini, t_envl *env_copy);

/*
 * validating input
 */
int		validator(char *input);
int		first_check(char *input, int it);
int		counting_pipes_or_delimeters(char *input, int it);
int		counting_quotes(char *input, int *it, char quote);
int		counting_redirect(char *input, int *it, char redirect);
int		write_redirect(char *input, int *it);
int		read_redirect(char *input, int *it);
int		last_check(char *input, int *it);

t_arg	*arguments_processing(t_shell *mini);

/*
 * parsing arguments
 */
char	*postparser(char *input, t_envl *env_copy);
char	*is_quote(char *input, int *it);
char	*is_db_quote(char *input, int *it, t_envl *env_copy);
char	*str_handler(char *input, int begin, int end);
char	*is_slash(char *input, int *it);
char	*is_dollar(char *input, int *it, t_envl *env_copy);
char	*key_handler(char *input, int begin, int end, t_envl *env_copy);
int		key_checker(char c);

/*
 * parser utils
 */
int		pass_whitespaces(char *input, int it);
int		opener(char *path, char flag);
int		find_file_name(char *input, int *it);

// printer
void	print_env_copy(t_shell *mini);
void	print_args(t_shell *mini);



#endif