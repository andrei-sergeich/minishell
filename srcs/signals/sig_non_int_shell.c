#include "../include/minishell.h"

void	sig_non_interactive_quit(int sig)
{
	char	*nbr;

	nbr = ft_itoa(sig);
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putendl_fd(nbr, STDERR_FILENO);
	free(nbr);
	nbr = NULL;
	g_ext_stat = 131;
}

void	sig_non_interactive_ctrl_c(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDERR_FILENO);
	g_ext_stat = 130;
}

void	sigs_non_interactive_shell(void)
{
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, sig_non_interactive_ctrl_c);
	signal(SIGQUIT, sig_non_interactive_quit);
}
