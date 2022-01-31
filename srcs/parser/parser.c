#include "../include/minishell.h"

void	parser(t_shell *mini, t_envl *env_copy)
{
	(void)env_copy;
	mini->input = readline(BEGIN(49, 32)"[minishell ]$ "CLOSE);
//	mini->input = ft_strdup("co'$USER' mma'n\\nn'dd000\\'00co\"mm\\\"\"an'dddd'aa'aaa");
//	mini->input = ft_strdup("ls co$PWD mma'n'aaa");
//	mini->input = ft_strdup("	'|'	ls	|	-la     '|' ss	qq");
//	mini->input = ft_strdup(">grep >  'lime'            test.txt | grep time > test | cat < 5");
//	mini->input = ft_strdup("<<test.txt grep ou < test3 llo");
//	mini->input = ft_strdup("ls <1 <2 <5 >'time'");
//	mini->input = ft_strdup(">0 >1 | ls");
//	mini->input = ft_strdup("cat <1 | ls -la");
//	printf("\nmini->input = %s\n\n", mini->input);
	if (!mini->input)
//		exit(0);
		exit(g_ext_stat);
	if (*mini->input)					/* If the line has any text in it, */
		add_history (mini->input);		/* save it on the history. */
	if (validator(mini->input) == 0)
	{
		mini->args = arguments_processing(mini);
		mini->cmds = commands_processing(mini);
//		mini->input = postparser(mini->input, env_copy);
	}
	free(mini->input);
	mini->input = NULL;
}
