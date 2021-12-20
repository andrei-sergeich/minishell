#include "../include/minishell.h"

int	pass_whitespaces(char *input, int it)
{
	while (input[it] && (ft_strchr("\t", input[it]) || ft_strchr(" ", input[it])))
		it++;
	return (it);
}

int	opener(char *path, char flag)
{
	int	fd;

	fd = -1;
	if (flag == 'I')
		fd = open(path, O_RDONLY);
	else if (flag == 'O')
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (flag == 'h')
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		//	g_ext_stat = 258;
		// ret_val -1???
		print_msg(1, strerror(errno), 258);
	}
	return (fd);
}

int	find_file_name(char *input, int *it)
{
	int fd;
	int begin;
	char *file_name;
	printf("input = |%s|\n", input);

//	(*it)++;
	*it = pass_whitespaces(input, (*it) + 1);
	printf("it = %c	%d\n", input[*it], *it);
	begin = *it;
	while (input[*it] && /*ft_isprint(input[*it]) && */input[*it] != ' ')
	{
//		printf("it = %c	%d\n", input[*it], *it);
		(*it)++;
	}
	file_name = ft_substr(input, begin, *it - begin);
	printf("file_name = |%s|\n", file_name);
	fd = opener(file_name, 'I');
	if (fd > 0)
	{
		printf("%d\n", fd);
		return (0);
	}
	return (1);
}