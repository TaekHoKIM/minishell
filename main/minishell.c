/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:14:41 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/17 21:28:46 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"

// cat을 실행해서 입력을 기다릴 때 ctrl \가  들어오면 ^\Quit: 3을 출력하고 
// 다시 readline을 기다린다.

// 지금부터 나오는 함수들은 과거에 readline을 구현해야 해서 필요했던 함수들이다.
// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

// getcwd 현재 디렉토리 받아오기

// $? 애초에 $는 전부 환경변수로 치환이 된다. $?는 특별하게 치환이 된다고 한다.
// 처음에는 0으로 초기화가 돼있다. 전에 실행했던 명령어의 종료 값을 출력한다고 한다.
// 그럼 치환부분을 어떻게 구현해야하는거지? 

// 정상 작동 안 하는 명령어들
// ls -l > outfile | cat /dev/urandom | cat | rm -rf outfile
// 위 명령어 같은 경우 bash에서는 정상 종료, 하지만 우리는 무한 루프에 걸림.

static void	initial_set(t_token_list *head, t_info *info,
	t_envp **env, char **envp)
{
	info->argv = NULL;
	info->cmd_cnt = 0;
	info->envp = NULL;
	info->here_doc_cnt = 0;
	info->i_fd = STDIN_FILENO;
	info->last_child_pid = 0;
	info->o_fd = STDOUT_FILENO;
	info->path = NULL;
	info->pid = NULL;
	info->pipe_cnt = 0;
	info->pipefd = NULL;
	info->exit_code = 0;
	set_terminal_not_print();
	bagic_set_parent_signal();
	head = NULL;
	*env = NULL;
	set_envp(env, envp);
}

static void	finish_set(t_token_list **head, t_info *info)
{
	t_token_list_free(head);
	here_doc_file_unlink(info->here_doc_cnt);
	info_terminal_signal_reset(info);
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_token_list	*head;
	t_envp			*env;
	t_info			info;

	(void)argc;
	(void)argv;
	initial_set(head, &info, &env, envp);
	while (1)
	{
		line = readline("minishell % ");
		if (line == NULL)
			ctrl_d_print_exit();
		add_history(line);
		if (tokenization(line, &head, env, info.exit_code) == FAIL)
			continue ;
		if (here_doc_preprocessor(head, &info) == FAIL)
			info.exit_code = EXIT_FAILURE;
		exec_process(head, env, &info);
		finish_set(&head, &info);
	}
	exit(EXIT_SUCCESS);
}
