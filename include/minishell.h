#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
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
	struct s_argl	*args;
	struct s_cmdl	*cmds;
}					t_shell;

typedef struct s_envl
{
	char			*line; // maybe delete
	char			*key;
	char			*value;
	struct s_envl	*next;
}					t_envl;

typedef struct s_argl
{
//	char			*arg_cleaned;
	char			*arg_origin;
	int				redirect;
	struct s_argl	*next;
}				t_argl;

typedef struct s_cmdl
{
	char			**command;
	int				in;
	int				out;
	int				pipe_fd[2];
	int				fork;
	pid_t			pid;
	struct s_rdr	*redir;
	struct s_cmdl	*next;
}				t_cmdl;

typedef struct s_redir
{
	char			*type;
	char			*name;
	struct s_redir	*next;
}				t_redir;

/*
 * utils
 */
void	*allocator(size_t size);
void	liberator(t_shell *mini);
void	initializator(t_shell *mini);
void	envl_lstdelone(t_envl *lst);
void	args_lstdelone(t_argl *lst);
void	cmds_lstdelone(t_cmdl *lst);
void	envl_destroy(t_envl **lst);
void	args_destroy(t_argl **lst);
void	cmds_destroy(t_cmdl **lst);
int		print_msg(int ret_val, char *message, int ext_stat);
int		cmds_lstsize(t_cmdl *cmds);

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
void	parser(t_shell *mini, t_envl *env_copy);

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

/*
 * processing arguments
 */
t_argl	*arguments_processing(t_shell *mini);
void	split_input(char *input, t_argl **args, t_shell *mini);
int		find_end(char *input, int it, int *flag);
void	args_lstadd_back(t_argl	**list, t_argl *new);
t_argl	*args_lstnew(char *arg_str, t_shell *mini);
void	args_lstdelnode(t_argl **args);
void	set_redirect(t_argl *args);

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
void	fd_opening(t_cmdl *cmds);

void	heredoc(t_cmdl *cmd, char *stop);


/*
 * processing commands
 */
t_cmdl	*commands_processing(t_shell *mini);
void	cmds_lstadd_back(t_cmdl	**list, t_cmdl *new);
t_cmdl	*cmds_lstnew(t_argl *args);
char	**write_cmd_to_array(t_argl *args, int quantity_lists);
int		find_full_command(t_argl *args);
t_redir	*redirect_processing(t_argl **args);
int		first_redirect(t_argl **args, t_redir **rdr);
void	redir_lstadd_back(t_redir **list, t_redir *new);
t_redir	*redir_lstnew(char *type, char *name);

/*
 * signals
 */
void	sigs_interactive_shell(void);
void	sig_interactive_ctrl_c(int sig);
void	sigs_non_interactive_shell(void);
void	sig_non_interactive_ctrl_c(int sig);
void	sig_non_interactive_quit(int sig);

/*
 * execution
 */
void	execute_cmds(t_shell *mini, t_cmdl *cmds);


/*
 * builtins
 */
int		builtin_checker(char *command);
void	builtin_executing(t_shell *mini, t_cmdl *cmds);
int		pwd_executing(void);

// printer
void	print_env_copy(t_envl *env_copy);
void	print_args(t_argl *args);
void	print_cmds(t_cmdl *cmds);
void	print_redir(t_cmdl *cmds);

#endif