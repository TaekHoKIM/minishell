/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 01:04:42 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/23 23:50:56 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	numeric_argument_fail(char *argv)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	exit(EXIT_ARGV_NOT_NUM);
}

int	built_exit(t_token_list *head, t_info *info)
{
	int	idx;
	int	b_exit_code;
	int	check;

	idx = 0;
	if (info->pipe_cnt != 0)
		return (FAIL);
	argv_set(head, info);
	printf("exit\n");
	if (info->argv[1] == NULL)
		exit (EXIT_SUCCESS);
	b_exit_code = ft_atoi(info->argv[1], &check);
	if (check == FAIL)
		numeric_argument_fail(info->argv[1]);
	else if (info->argv[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_exit_code = 1;
		return (SUCCESS);
	}
	exit((unsigned char)b_exit_code);
	return (SUCCESS);
}
