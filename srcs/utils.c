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

void	*allocator(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("Could not malloc");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void	lstdelone(t_envl *lst)
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
		lstdelone(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	liberator(t_shell *mini)
{
	envl_destroy(&mini->env_copy);
	free(mini);
}