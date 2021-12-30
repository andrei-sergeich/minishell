#include "../include/minishell.h"

int	find_full_command(t_argl *args)
{
	int		quantity;
	t_argl	*tmp;

	if (!args)
		return (0);
	tmp = args;
	quantity = 0;
	if (tmp->redirect == 0)
		quantity = 1;
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
//	cmds->redir = ms_extract_redirects(&args);
	quantity_lists = find_full_command(args);
	element->command = write_cmd_to_array(args, quantity_lists);
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
			cmds_lstadd_back(&mini->cmds, cmds_lstnew(cmd_begin));
			cmd_begin = tmp->next;
		}
		printf("tmp->arg_cleaned - |%s|\n", tmp->arg_cleaned);
		tmp = tmp->next;
	}
	cmds_lstadd_back(&mini->cmds, cmds_lstnew(cmd_begin));
	return (mini->cmds);
}
