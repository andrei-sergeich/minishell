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

	if ((*args)->head) {
		(*args)->head->next = (*args)->next;
	}
	if ((*args)->next) {
		(*args)->next->head = (*args)->head;
	}
	free((*args)->arg_cleaned);
	(*args)->arg_cleaned = NULL;
	free((*args));
//	head->head = NULL;
//	printf("*%p*\n", args);
//	printf("*%p*\n", head);
//	args_lstdelone(*args);
//	if ((*args)->next)
//	{
//		next = (*args)->next;
//		prev = (*args)->head;
//		free((*args)->arg_cleaned);
//		(*args)->arg_cleaned = NULL;
//		free((*args));
//		next->head = prev;
//		*args = next;
//	}
//	else
//	{
////		*args = (*args)->head;
//		prev = (*args)->head;
//		free((*args)->arg_cleaned);
//		(*args)->arg_cleaned = NULL;
//		free((*args)->next);
////		prev->next = NULL;
////		(*args)->next = NULL;
//		*args = (*args)->head;
//	}
//	if ((*args)->next)
//	{
//		(*args) = (*args)->next;
////		free(prev->arg_cleaned);
//		free((*args)->head->arg_cleaned);
////		prev->arg_cleaned = NULL;
////		free(prev);
//		free((*args)->head);
//		(*args)->head = (*args)->head->head;
//	}
//	else
//	{
//		(*args) = (*args)->head;
//		free((*args)->next->arg_cleaned);
//		free((*args)->next);
//	}
}

int	first_redirect(t_argl **args, t_redir **rdr)
{
	while (*args)
	{
		printf("=%s=\n", (*args)->arg_cleaned);
		if ((*args)->redirect == 1)
		{
			redir_lstadd_back(rdr, redir_lstnew((*args)->arg_cleaned, (*args)->next->arg_cleaned));
//			if (!args->next->next)
//			{
			args_lstdelnode(args);
			args_lstdelnode(args);
//				return (1);
//			}
//			args = args->next->next;
		}
		if ((*args)->redirect == 0)
			break ;
		(*args) = (*args)->next;
	}
	return (0);
}

t_redir	*redirect_processing(t_argl **args)
{
	t_redir	*rdr;
	t_argl	*tmp;
//	t_argl	*prev;

	if (!args)
		return (NULL);
	rdr = NULL;
//	if (first_redirect(&args, &rdr) == 1)
//		return (rdr);

//	first_redirect(&tmp, &rdr);
	if ((*args)->redirect == 1)
	{
		redir_lstadd_back(&rdr, redir_lstnew((*args)->arg_cleaned, (*args)->next->arg_cleaned));
//		args_lstdelnode(&tmp);
//		args_lstdelnode(&tmp);
//		prev = (*args);
		(*args) = (*args)->next;
//		free(prev->arg_cleaned);
		free((*args)->head->arg_cleaned);
//		prev->arg_cleaned = NULL;
//		free(prev);
		free((*args)->head);
		(*args)->head = NULL;
//		prev = (*args);
		(*args) = (*args)->next;
//		free(prev->arg_cleaned);
		free((*args)->head->arg_cleaned);
//		prev->arg_cleaned = NULL;
//		free(prev);
		free((*args)->head);
		(*args)->head = NULL;
	}
	printf("1 - %p, %s\n", *args, (*args)->arg_cleaned);
	tmp = *args;
	printf("*%p*\n", tmp);
	while ((*args)->next)
	{
//		printf("=%s=\n", (*args)->next->arg_cleaned);
		if (ft_strcmp((*args)->arg_cleaned, "|") == 0)
			break ;
		if ((*args)->next->redirect == 1)
		{
			redir_lstadd_back(&rdr, redir_lstnew((*args)->next->arg_cleaned, (*args)->next->next->arg_cleaned));
			args_lstdelnode(&((*args)->next));
			args_lstdelnode(&((*args)->next));
		}
		if ((*args)->next && (*args)->next->redirect != 1)
			(*args) = (*args)->next;
	}
	while ((*args)->head)
		(*args) = (*args)->head;
//	while (tmp->next)
//	{
////		printf("=%s=\n", tmp->arg_cleaned);
//		if (ft_strcmp(tmp->arg_cleaned, "|") == 0)
//			break ;
//		if (tmp->next->redirect == 1)
//		{
//			redir_lstadd_back(&rdr, redir_lstnew(tmp->next->arg_cleaned, tmp->next->next->arg_cleaned));
//			args_lstdelnode(&tmp->next);
//			args_lstdelnode(&tmp->next);
//		}
//		if (tmp->next && tmp->next->redirect != 1)
//			tmp = tmp->next;
//	}
	return (rdr);
}

int	find_full_command(t_argl *args)
{
	int		quantity;
	t_argl	*tmp;

	if (!args)
		return (0);
	tmp = args;
//	quantity = 0;
//	if (tmp->redirect == 0)
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
//	t_argl *tmp = args->next->next;
//	print_args(tmp);
	element = (t_cmdl *)malloc(sizeof(t_cmdl));
	if (!element || !args)
		return (NULL);
//	printf("1 - %p\n", args);
//	printf("1.1 - %p\n", args->next->next);
//	printf("\n");
//	print_args(args);
	element->redir = NULL;
//	tmp = args->next->next;
	element->redir = redirect_processing(&args);
//	printf("2 - %p\n", args);
//	args = tmp;
//	printf("3 - %p\n", args);
//	args = tmp;
	print_args(args);
	quantity_lists = find_full_command(args);
	element->command = write_cmd_to_array(args, quantity_lists);
//	redir_check(args);
	element->in = 0;
	if (args->redirect == 1)
		element->out = 3;
	else
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

t_cmdl	*commands_processing(t_shell *mini)
{
	t_argl	*tmp;
	t_argl	*cmd_begin;

	if (mini->args == NULL)
		return (NULL);
//	printf("4.1 - %p\n", mini->args);
//	tmp = mini->args;
//	cmd_begin = tmp;
//	if ((ft_strcmp(tmp->arg_cleaned, "|")) == 0)
//		tmp = tmp->next;
//	while (tmp)
//	{
//		if ((ft_strcmp(tmp->arg_cleaned, "|")) == 0)
//		{
//			cmds_lstadd_back(&mini->cmds, cmds_lstnew(cmd_begin));
//			cmd_begin = tmp->next;
//		}
////		printf("tmp->arg_cleaned - |%s|\n", tmp->arg_cleaned);
//		tmp = tmp->next;
//	}
//	cmds_lstadd_back(&mini->cmds, cmds_lstnew(cmd_begin));
//	mini->args = mini->args->next->next;
//	printf("4.2 - %p\n", mini->args);
//	printf("4.2.1 - %p\n", mini->args->next);
//	printf("4.2.1 - %p\n", mini->args->next->next);
	cmd_begin = mini->args;
	if ((ft_strcmp(mini->args->arg_cleaned, "|")) == 0)
		mini->args = mini->args->next;
	while (mini->args)
	{
		if ((ft_strcmp(mini->args->arg_cleaned, "|")) == 0)
		{
			cmds_lstadd_back(&mini->cmds, cmds_lstnew(cmd_begin));
			cmd_begin = mini->args->next;
		}
//		printf("tmp->arg_cleaned - |%s|\n", tmp->arg_cleaned);
		printf("4.2 - %p %s\n", mini->args->head, mini->args->arg_cleaned);
		mini->args = mini->args->next;
	}
	cmds_lstadd_back(&mini->cmds, cmds_lstnew(cmd_begin));
	printf("4.2 - %p\n", mini->args->head);
	while (mini->args->head)
		mini->args = mini->args->head;
	printf("4.2 - %p\n", mini->args);
	return (mini->cmds);
}
