#include "../include/minishell.h"

int	print_msg(int ret_val, char *message, int ext_stat)
{
	write(2, "minishell: ", 11);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	(void)ext_stat;
//	g_ext_stat = ext_stat;
	return (ret_val);
}

void	envl_lstdelone(t_envl *lst)
{
	if (!lst)
		return ;
	free(lst->line);
	lst->line = NULL;
	free(lst->key);
	lst->key = NULL;
	free(lst->value);
	lst->value = NULL;
	free(lst);
	lst = NULL;
}

void	envl_destroy(t_envl **lst)
{
	t_envl	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		envl_lstdelone(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}


