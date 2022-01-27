#include "../include/minishell.h"

void	print_env_copy(t_envl *env_copy)
{
	if (env_copy == NULL)
		return ;
	while (env_copy)
	{
		printf("%s\n", env_copy->line);
		printf("%s=%s\n", env_copy->key, env_copy->value);
		env_copy = env_copy->next;
	}
}

void	print_args(t_argl *args)
{
	if (args == NULL)
		return ;
	while (args)
	{
		printf("args origin - |%s| \t %d\n", args->arg_origin, args->redirect);
		args = args->next;
	}
}

void	print_cmds(t_cmdl *cmds)
{
	int		it;
	t_redir	*tmp;

	if (cmds == NULL || !cmds->command)
		return ;
	while (cmds)
	{
		it = 0;
		while (cmds->command[it])
		{
			printf("cmds command[%d] - |%s|\t in - |%d|\t out - |%d|\n", it, cmds->command[it], cmds->in, cmds->out);
			it++;
		}
		tmp = (t_redir *) cmds->redir;
//		if (tmp == NULL)
//			break;
		while (tmp)
		{
			printf("redirect type - |%s| \t name - |%s|\n", tmp->type, tmp->name);
			tmp = tmp->next;
		}
		cmds = cmds->next;
	}
}

void	print_redir(t_cmdl *cmds)
{
	t_redir	*tmp;

	if (cmds == NULL)
		return ;
	while (cmds)
	{
		tmp = (t_redir *) cmds->redir;
		if (tmp == NULL)
			break ;
		while (tmp)
		{
			printf("redirect type - |%s| \t name - |%s|\n", tmp->type, tmp->name);
			tmp = tmp->next;
		}
		cmds = cmds->next;
	}
}

int	print_msg(int ret_val, char *message, int ext_stat)
{
//	write(2, "minishell: ", 11);
//	write(2, message, ft_strlen(message));
//	write(2, "\n", 1);
	ft_putstr_fd(BEGIN(49, 32)"[minishell ]$ "CLOSE, STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	(void)ext_stat;
//	g_ext_stat = ext_stat;
	return (ret_val);
}

//int	ms_error(char *str)
void	error_msg(char *message)
{
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	else
		perror("Error");
//	g_ext_stat = 128;
//	return (1);
}

void	no_such_message(char *message)
{
	ft_putstr_fd(BEGIN(49, 32)"[minishell ]$ "CLOSE, STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}