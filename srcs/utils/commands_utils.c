#include "../include/minishell.h"

int	cmds_lstsize(t_cmdl *cmds)
{
	int	count;

	if (!cmds)
		return (0);
	count = 0;
	while (cmds)
	{
//		maybe if (cmds->command[0])
		cmds = cmds->next;
		count++;
	}
	return (count);
}

void	redir_lstdelone(t_redir *lst)
{
	if (!lst)
		return ;
	free(lst->type);
	lst->type = NULL;
	free(lst->name);
	lst->name = NULL;
	free(lst);
	lst = NULL;
}

void	redir_destroy(t_redir **lst)
{
	t_redir	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		redir_lstdelone(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	cmds_lstdelone(t_cmdl *lst)
{
	int		it;
	t_redir	*tmp;

	it = 0;
	if (!lst)
		return ;
	while (lst->command[it])
	{
		if (lst->command == NULL)
			break;
		free(lst->command[it]);
		lst->command[it] = NULL;
		it++;
	}
	free(lst->command);
	lst->command = NULL;
	tmp = (t_redir *) lst->redir;
	redir_destroy(&tmp);
	free(lst);
	lst = NULL;
}

void	cmds_destroy(t_cmdl **lst)
{
	t_cmdl	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		cmds_lstdelone(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}