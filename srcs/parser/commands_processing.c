#include "../include/minishell.h"

t_cmdl	*cmds_lstnew(t_argl *args)
{
	t_cmdl	*cmds;
	int		quantity;

	cmds = (t_cmdl *)malloc(sizeof(t_cmdl));
	if (!cmds || !args)
		return (NULL);
	cmds->redir = NULL;
	cmds->redir = ms_extract_redirects(&args);
	quantity = get_cmd_size(args);
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
	t_argl	*head;

	if (mini->args == NULL)
		return (NULL);
	mini->cmds = NULL;
	tmp = mini->args;
	while (tmp)
	{
		if ((ft_strcmp(tmp->arg_cleaned, "|")) == 0)
		{
			cmds_lstadd_back(&mini->cmds, cmds_lstnew(tmp));
		}
	}
	return (mini->cmds);
}
