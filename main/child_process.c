/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:42:24 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/04 20:51:06 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define STDIN 0
#define STDOUT 1

			// 자식프로세스라는 함수를 하나 만들어서 거기에서 여러가지
			// 자식이 해야할 일을 처리
			// 대표적으로 infile, outfile을 확인해서 열어야 하면 열고
			// 아니면 파이프로 dup을 떠서 한다.
			// 그리고 확실하게 모든 fd를 close해줘야한다.
			// 또 중요한건 cmd가 없을 수도 있다는 점을 생각해야 한다.
			// ex) < infile | > outfile
			// wait을 해주는 함수를 하나 만들어서 자식 프로세스의 종료
			// 코드들을 전부 받아준다. 근데 $?명령어가 있어서 이 부분을
			// 생각해서 마지막 자식 프로세스의 종료 코드는 기억하고 있어야 한다.
			// 그리고 자식과 부모의 시그널 핸들링이 다르기 때문에 그 부분을 기억하고
			// 잘 처리해야한다.
			

static void	pipe_set(int i_fd, int o_fd)
{
	if (i_fd != NO_CHANGE && dup2(i_fd, STDIN) == FAIL)
	{
		ft_perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (o_fd != NO_CHANGE && dup2(o_fd, STDOUT) == FAIL)
	{
		ft_perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (i_fd != NO_CHANGE && close(i_fd) == FAIL)
	{
		ft_perror("close");
		exit(EXIT_FAILURE);
	}
	if (o_fd != NO_CHANGE && close(o_fd) == FAIL)
	{
		ft_perror("close");
		exit(EXIT_FAILURE);
	}
}

// NO_CHANGE, NO_CHANGE

// NO_CHANGE, pipe
// NO_CHANGE, file

// pipe, NO_CHANGE

// file, NO_CHANGE

// pipe pipe

// pipe file

// file pipe

// file file


static void	child_fd_set(t_info *info, int i)
{
	if (i == 0 && info->i_fd == STDIN && info->o_fd == STDOUT)
		pipe_set(NO_CHANGE, info->pipefd[i][1]);
	else if (i == 0 && info->i_fd == STDIN && info->o_fd != STDOUT)
		pipe_set(NO_CHANGE, info->o_fd);
	else if (i == 0 && info->i_fd != STDIN && info->o_fd == STDOUT 
			&& i == info->pipe_cnt)
		pipe_set(info->i_fd, NO_CHANGE);
	else if (i == 0 && info->i_fd != STDIN && info->o_fd != STDOUT)
		pipe_set(info->i_fd, info->o_fd);
	else if (i == 0 && i == info->pipe_cnt)
		pipe_set(NO_CHANGE, NO_CHANGE);
	else if (i == info->pipe_cnt && info->i_fd == STDIN && info->o_fd == STDOUT)
		pipe_set(info->pipefd[i - 1][0], NO_CHANGE);
	else if (i == info->pipe_cnt && info->i_fd != STDIN && info->o_fd != STDOUT)
		pipe_set(info->i_fd, info->o_fd);
	else if (i == info->pipe_cnt && info->i_fd != STDIN && info->o_fd == STDOUT)
		pipe_set(info->i_fd, NO_CHANGE);
	else if (i == info->pipe_cnt && info->i_fd == STDIN && info->o_fd != STDOUT)
		pipe_set(info->pipefd[i - 1][0], info->o_fd);
	else if (info->i_fd == STDIN && info->o_fd == STDOUT)
		pipe_set(info->pipefd[i - 1][0], info->pipefd[i][1]);
	else if (info->i_fd == STDIN && info->o_fd != STDOUT)
		pipe_set(info->pipefd[i - 1][0], info->o_fd);
	else if (info->i_fd != STDIN && info->o_fd == STDOUT)
		pipe_set(info->i_fd, info->pipefd[i][1]);
	else if (info->i_fd != STDIN && info->o_fd != STDOUT)
		pipe_set(info->i_fd, info->o_fd);
}

static char	*access_check(char **path, char *cmd)
{
	char	*res;
	char	*tmp;
	ssize_t	i;

	i = 0;
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		res = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(res, F_OK | X_OK) == 0)
			return (res);
		free(res);
		i++;
	}
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	return (cmd);
}

void	child_process(t_info *info, int i)
{
	char	*cmd_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	child_fd_set(info, i);
	cmd_path = access_check(info->path, info->argv[0]);
	execve(cmd_path, info->argv, info->envp);
	ft_perror(cmd_path);
	exit(CMD_NOT_FOUND);
}