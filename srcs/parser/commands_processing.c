#include "../include/minishell.h"

void	redir_lstadd_back(t_redir **list, t_redir *new)
{
	t_redir	*last;

	if (!list || !new)
		exit(EXIT_FAILURE); 			/* or return */
	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*list = new;
}

t_redir	*redir_lstnew(char *type, char *name)
{
	t_redir	*element;

	element = (t_redir *)malloc(sizeof(t_redir));
	if (!element)
		return (NULL);
	element->type = ft_strdup(type);
	element->name = ft_strdup(name);
	element->next = NULL;
	return (element);
}

void	args_lstdelnode(t_argl **args)
{
	t_argl	*next;

	if (!args || !(*args))
		return ;
	next = (*args)->next;
	free((*args)->arg_origin);
	(*args)->arg_origin = NULL;
	free((*args));
	*args = next;
}

int	first_redirect(t_argl **args, t_redir **rdr)
{
	while (*args)
	{
		if ((*args)->redirect == 1)
		{
			redir_lstadd_back(rdr, redir_lstnew((*args)->arg_origin, (*args)->next->arg_origin));
			if (!(*args)->next->next)
			{
				(*args) = (*args)->next->next;
				return (1);
			}
			(*args) = (*args)->next->next;
		}
		if ((*args)->redirect == 0)
			break ;
	}
	return (0);
}

t_redir	*redirect_processing(t_argl **args)
{
	t_redir	*rdr;
	t_argl	*tmp;

	if (!args || !(*args))
		return (NULL);
	rdr = NULL;
	if (first_redirect(args, &rdr) == 1)
		return (rdr);
	tmp = *args;
//	printf("*%p*\n", tmp);
	while (tmp->next)
	{
		if (ft_strcmp(tmp->arg_origin, "|") == 0)
			break ;
		if (tmp->next->redirect == 1)
		{
			redir_lstadd_back(&rdr, redir_lstnew(tmp->next->arg_origin, tmp->next->next->arg_origin));
			args_lstdelnode(&tmp->next);
			args_lstdelnode(&tmp->next);
		}
		if (tmp->next && tmp->next->redirect != 1)
			tmp = tmp->next;
	}
	return (rdr);
}

int	find_full_command(t_argl *args)
{
	int		quantity;
	t_argl	*tmp;

	if (!args)
		return (0);
	tmp = args;
	quantity = 1;
	if (ft_strcmp("|", tmp->arg_origin) == 0)
		return (0);
	while (tmp->next)
	{
//		printf("tmp->arg_pure is - %s\n", tmp->arg_origin);
//		if (ft_strcmp(tmp->arg_origin, "|") == 0)
//		{
//			it = 0;
//			printf("i is - %d\n", it);
//			break ;
//		}
		tmp = tmp->next;
		if (ft_strcmp(tmp->arg_origin, "|") == 0)
			return (quantity);
//		if (tmp->redirect == 0)
//			it++;
		quantity++;
	}
//	printf("i is - %d\n", it);
	return (quantity);
}

char	**write_cmd_to_array(t_argl *args, int quantity_lists)
{
	int		it;
	char	**arg_arr;

	it = 0;
	arg_arr = malloc(sizeof(char *) * (quantity_lists + 1));
	if (!arg_arr)
		return (NULL);
	while (args && (quantity_lists != 0))
	{
		arg_arr[it] = ft_strdup(args->arg_origin);
		it++;
		quantity_lists--;
		args = args->next;
	}
	arg_arr[it] = NULL;
	return (arg_arr);
}

t_cmdl	*cmds_lstnew(t_argl *args)
{
	t_cmdl	*element;
	int		quantity_lists;

	element = (t_cmdl *)malloc(sizeof(t_cmdl));
	if (!element || !args)
		return (NULL);
	element->redir = NULL;
	element->redir = (struct s_rdr *) redirect_processing(&args);
//	print_args(args);
	quantity_lists = find_full_command(args);
	element->command = write_cmd_to_array(args, quantity_lists);
	element->in = 0;
//	if (args->redirect == 1)
//		element->out = 3;
//	else
	element->out = 1;
	element->next = NULL;
	return (element);
}

void	cmds_lstadd_back(t_cmdl	**list, t_cmdl *new)
{
	t_cmdl	*last;

	if (!list || !new)
		exit(EXIT_FAILURE); 			/* or return */
	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*list = new;
}

void	clean_cmd_and_filename(t_shell *mini)
{
	t_cmdl	*cmd;
	t_redir	*rdr;
	int		it;

	cmd = mini->cmds;
	rdr = (t_redir *) mini->cmds->redir;
	while (cmd)
	{
		if (cmd->command)
		{
			it = 0;
			while (cmd->command[it])
			{
				cmd->command[it] = postparser(cmd->command[it], mini->env_copy);
				it++;
			}
		}
		while (rdr)
		{
			rdr->name = postparser(rdr->name, mini->env_copy);
			rdr = rdr->next;
		}
		cmd = cmd->next;
	}
}

void	fd_opening(t_cmdl *cmds)
{
	t_redir	*tmp;
	int it;

	if (cmds == NULL)
		return ;
	while (cmds)
	{
		it = 0;
		tmp = (t_redir *) cmds->redir;
		while (tmp)
		{
			printf("%d * redirect type - |%s| \t name - |%s|\n", it, tmp->type, tmp->name);
			if (ft_strcmp("<", tmp->type) == 0)
				cmds->in = opener(tmp->name, 'I');
			if (ft_strcmp(">", tmp->type) == 0)
				cmds->out = opener(tmp->name, 'O');
			if (ft_strcmp(">>", tmp->type) == 0)
				cmds->out = opener(tmp->name, 'A');
			tmp = tmp->next;
			it++;
		}
		printf("in - |%d| \t out - |%d|\n", cmds->in, cmds->out);
		cmds = cmds->next;
	}
}

t_cmdl	*commands_processing(t_shell *mini)
{
	t_argl	*tmp;
	t_argl	*cmd_begin;

	if (mini->args == NULL)
		return (NULL);
	tmp = mini->args;
	cmd_begin = tmp;
	if ((ft_strcmp(tmp->arg_origin, "|")) == 0)
		tmp = tmp->next;
	while (tmp)
	{
		if ((ft_strcmp(tmp->arg_origin, "|")) == 0)
		{
//			printf("**\nfrom commands_processing\n%s\n**", tmp->arg_origin);
			cmds_lstadd_back(&mini->cmds, cmds_lstnew(cmd_begin));
			cmd_begin = tmp->next;
//			printf("%s\n", cmd_begin->arg_origin);
		}
		tmp = tmp->next;
	}
	cmds_lstadd_back(&mini->cmds, cmds_lstnew(cmd_begin));
	clean_cmd_and_filename(mini);
	fd_opening(mini->cmds);
	return (mini->cmds);
}
