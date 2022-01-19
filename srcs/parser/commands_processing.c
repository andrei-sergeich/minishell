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
	t_argl	*prev;
	t_argl	*next;

	if (!args || !(*args))
		return ;
	next = (*args)->next;
	free((*args)->arg_cleaned);
	(*args)->arg_cleaned = NULL;
	free((*args));
	*args = next;
}

int	first_redirect(t_argl **args, t_redir **rdr)
{
	while (*args)
	{
		if ((*args)->redirect == 1)
		{
			redir_lstadd_back(rdr, redir_lstnew((*args)->arg_cleaned, (*args)->next->arg_cleaned));
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
		if (ft_strcmp(tmp->arg_cleaned, "|") == 0)
			break ;
		if (tmp->next->redirect == 1)
		{
			redir_lstadd_back(&rdr, redir_lstnew(tmp->next->arg_cleaned, tmp->next->next->arg_cleaned));
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
	if (ft_strcmp("|", tmp->arg_cleaned) == 0)
		return (0);
	while (tmp->next)
	{
//		printf("tmp->arg_pure is - %s\n", tmp->arg_cleaned);
//		if (ft_strcmp(tmp->arg_cleaned, "|") == 0)
//		{
//			it = 0;
//			printf("i is - %d\n", it);
//			break ;
//		}
		tmp = tmp->next;
		if (ft_strcmp(tmp->arg_cleaned, "|") == 0)
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
		arg_arr[it] = ft_strdup(args->arg_cleaned);
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
	element->redir = redirect_processing(&args);
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

t_cmdl	*cmds_cleaning(t_shell *mini)
{
	t_cmdl	*tmp;


	tmp = mini->cmds;
	while (tmp)
	{
		if (tmp->command)
		{
			int it = 0;
			while (tmp->command[it])
			{
				tmp->command[it] = postparser(tmp->command[it], mini->env_copy);
				it++;
			}
		}
		tmp = tmp->next;
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
	if ((ft_strcmp(tmp->arg_cleaned, "|")) == 0)
		tmp = tmp->next;
	while (tmp)
	{
		if ((ft_strcmp(tmp->arg_cleaned, "|")) == 0)
		{
//			printf("**\nfrom commands_processing\n%s\n**", tmp->arg_cleaned);
			cmds_lstadd_back(&mini->cmds, cmds_lstnew(cmd_begin));
			cmd_begin = tmp->next;
//			printf("%s\n", cmd_begin->arg_cleaned);
		}
		tmp = tmp->next;
	}
	cmds_lstadd_back(&mini->cmds, cmds_lstnew(cmd_begin));
	cmds_cleaning(mini);
	return (mini->cmds);
}
