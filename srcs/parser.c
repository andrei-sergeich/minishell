#include "../include/minishell.h"

void	parser(t_shell *mini, t_envl *env_copy)
{
	(void)env_copy;
	mini->input = NULL;
//	mini->input = readline(BEGIN(49, 32)"[minishell ]$ "CLOSE);
//	mini->input = ft_strdup("co'$USER' mma'n\\nn'dd000\\'00co\"mm\\\"\"an'dddd'aa'aaa");
//	mini->input = ft_strdup("ls co'$USER' mma'n'aaa");
//	mini->input = ft_strdup("	'	'	ls	|	-la");
	mini->input = ft_strdup("grep time <           test.txt ; grep time < test");
	printf("mini->input = %s\n\n", mini->input);
	if (!mini->input)
		exit(0);
//	if (*mini->input)					/* If the line has any text in it, */
//		add_history (mini->input);		/* save it on the history. */
//	preparser(mini->input);
//	mini->input = pass_whitespaces(mini->input);
	if (validator(mini->input) == 0)
	{
		mini->args = arguments_processing(mini);
//		mini->input = postparser(mini->input, env_copy);
	}
//	printf("%p\n", mini->input);
	free(mini->input);
}
