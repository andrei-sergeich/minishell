#include "../include/minishell.h"

void	sig_interactive_ctrl_c(int sig)
{
	(void)sig;
	write (STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_ext_stat = 1;
}

void	sigs_interactive_shell(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, &sig_interactive_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
