/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 01:04:42 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/15 02:29:21 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_exit_argv(char *argv)
{
	int	idx;

	idx = 0;
	if (argv == NULL)
		exit(EXIT_SUCCESS);
	while (argv[idx] != '\0')
	{
		if (!('0' <= argv[idx] && argv[idx] <= '9'))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(argv, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			return (FAIL);
		}
		idx++;
	}
	return (SUCCESS);
}

int	built_exit(t_token_list *head, t_info *info)
{
	int	idx;
	int	exit_code;

	idx = 0;
	if (info->pipe_cnt != 0)
		return (FAIL);
	argv_set(head, info);
	printf("exit\n");
	if (check_exit_argv(info->argv[1]) == FAIL)
		exit(EXIT_ARGV_NOT_NUM);
	exit_code = ft_atoi(info->argv[1]);
	exit((unsigned char)exit_code);
	return (SUCCESS);
}
