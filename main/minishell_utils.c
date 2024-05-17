/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:14:36 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/17 18:15:08 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_malloc(size_t size, size_t cnt)
{
	void	*tmp;

	tmp = malloc(size * cnt);
	if (tmp == NULL)
		exit(EXIT_FAILURE);
	return (tmp);
}

int	ft_perror(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(str);
	return (FAIL);
}

int	ft_chdir(char *path, t_info *info)
{
	if (chdir(path) == FAIL)
	{
		ft_perror(path);
		info->exit_code = 1;
		return (FAIL);
	}
	return (SUCCESS);
}

void	ctrl_d_print_exit(void)
{
	ft_putstr_fd("\033[1A", STDERR_FILENO);
	ft_putstr_fd("\033[12C", STDERR_FILENO);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(EXIT_SUCCESS);
}

void	info_terminal_signal_reset(t_info *info)
{
	array_2d_free((void **)info->argv);
	info->argv = NULL;
	info->cmd_cnt = 0;
	array_2d_free((void **)info->envp);
	info->envp = NULL;
	info->here_doc_cnt = 0;
	info->i_fd = STDIN_FILENO;
	info->last_child_pid = 0;
	info->o_fd = STDOUT_FILENO;
	array_2d_free((void **)info->path);
	info->path = NULL;
	free(info->pid);
	info->pid = NULL;
	info->pipe_cnt = 0;
	array_2d_free((void **)info->pipefd);
	info->pipefd = NULL;
	set_terminal_not_print();
	bagic_set_parent_signal();
}
