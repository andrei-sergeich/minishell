#include "../include/minishell.h"

t_argl	*args_lstnew(char *arg_str, t_shell *mini)
{
	t_argl	*element;

	(void)mini;
	element = (t_argl *)malloc(sizeof(t_argl));
	if (!element)
		return (NULL);
//	element->arg_cleaned = ft_strdup(arg_str);
//	element->arg_origin = postparser(arg_str, mini->env_copy);
	element->arg_origin = ft_strdup(arg_str);
	element->redirect = 0;
	element->next = NULL;
	free(arg_str);
	return (element);
}

void	args_lstadd_back(t_argl	**list, t_argl *new)
{
	t_argl	*last;

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
