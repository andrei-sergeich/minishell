#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *input;

	(void)argc;
	(void)argv;
	(void)envp;
//	rl_outstream = stderr;
	g_status = 0;
	while (1)
	{
		input = readline(BEGIN(49, 32)"minishell$ "CLOSE);
		if (!input)
			break;
		if (input && *input)			/* If the line has any text in it, */
			add_history (input);		/* save it on the history. */
		free(input);
	}
	exit(9);
}
