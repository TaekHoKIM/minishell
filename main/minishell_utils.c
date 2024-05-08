/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:14:36 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/08 16:11:44 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	*ft_malloc(size_t size, size_t cnt)
{
	void	*tmp;

	tmp = malloc(sizeof(size) * cnt);
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

void	ctrl_d_print_exit()
{
	ft_putstr_fd("\033[1A", STDOUT_FILENO); // 현재 커서의 위치를 한칸 위로 올려줌 
	ft_putstr_fd("\033[12C", STDOUT_FILENO); // 현재 커서의 위치를 12번째칸으로 이동
	ft_putstr_fd("exit\n", STDOUT_FILENO); // exit를 출력
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
	info->o_fd = STDOUT_FILENO;
	array_2d_free((void **)info->path);
	info->path = NULL;
	free(info->pid);
	info->pid = NULL;
	info->pipe_cnt = 0;
	array_2d_free((void **)info->pipefd);
	info->pipefd = NULL;
	set_terminal_not_print();
	set_parent_signal();
}
