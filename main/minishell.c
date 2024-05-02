/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:14:41 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/02 21:30:52 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"

// cat을 실행해서 입력을 기다릴 때 ctrl \가  들어오면 ^\Quit: 3을 출력하고 
// 다시 readline을 기다린다.

// 부모는 ignore하고 자식은 default

// if you don't plan to do bonus part the following func not 
// required opendir, readdir, closedir, stat, lstat, fstat
// 지금부터 나오는 함수들은 과거에 readline을 구현해야 해서 필요했던 함수들이다.
// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

// waitpid를 좀 더 자세하게 사용하기 위해서 쓰는 함수 wait3, wait4

// export를 내가 만들어야 하기 때문에 getenv는 사용 가치가 상당히 떨어진다.
// 처음에 가지고 온 envp를 파싱해서 자료구조로 만든다.
// c++에서 map이라고 부르는 방식으로 하셨다. 누가? 경준님이

// signal의 고급 함수들 sigaction, sigemptyset, sigaddset
// 경준님은 사용하셨으나 꼭 필요한가? 그건 아니다.

// getcwd 현재 디렉토리 받아오기

// tcsetattr함수로 ^C가 출력되지 않게 하기

int	do_nothing(void)
{
	return (NONE);
}

// arg 개수 세고
// < access, last in redirection index save
// > open, acess, last out redirection index save
// << limiter save
// >> open option change
// bash에서 history명령어에 대해서, 내가 구현해야하는가?, 구현되어있는가?

// void	access_check(t_token_list *head, t_envp *ev)
// {
// 	t_token_list	*tmp;

// 	tmp = head;
// 	while (tmp != NULL)
// 	{
// 		if (tmp->type == CMD)
// 			access()
// 	}
// }

// $? 애초에 $는 전부 환경변수로 치환이 된다. $?는 특별하게 치환이 된다고 한다.
// 처음에는 0으로 초기화가 돼있다. 전에 실행했던 명령어의 종료 값을 출력한다고 한다.
// 그럼 치환부분을 어떻게 구현해야하는거지? 
// 파이프엑스를 가지고 와서 그냥 파일 부분들을 변경, 명령어마다 파일을 구분 지어서 해줘야 함.

static int	here_doc_preprocessor(t_token_list *head, t_info *info)
{
	char	*tmp;
	char	*filename;

	info->here_doc_cnt = 0;
	while (head != NULL)
	{
		if (head->type == IN_D2_ARG)
			fake_here_doc(head->token);
		if (head->type == IN_OPEN_D2)
		{
			info->here_doc_cnt++;
			tmp = ft_itoa(info->here_doc_cnt);
			filename = ft_strjoin(".temp", tmp);
			free(tmp);	
			if (here_doc(filename, head->token) == FAIL)
			{
				here_doc_file_unlink(info->here_doc_cnt);
				return (FAIL);
			}
			free(head->token);
			head->token = filename;
		}
		head = head->next;
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_token_list	*head;
	t_envp			*env;
	t_info			info;

	set_terminal_not_print();
	set_parent_signal();
	set_envp(&env, envp);
	rl_event_hook = do_nothing;
	while (1)
	{
		line = readline("minishell % ");
		if (line == NULL)
		{
			write(STDOUT_FILENO, "\x1b[1Aexit\n", 8);
			exit(EXIT_SUCCESS);
		}
		add_history(line);
		tokenization(line, &head);
		if (here_doc_preprocessor(head, &info) == FAIL)
			continue ;
		here_doc_file_unlink(info.here_doc_cnt);
		display_list(&head);
		// access_check(head);
		t_token_list_free(head);
		free(line);
		// if (pid == 0)
		// {
		// 	signal(SIGINT, SIG_DFL);
		// }
		// else
		// {
		// 	signal(SIGINT, SIG_IGN);
		// }
		// last wait_pid;
		// 다 진행하고 signal(SIGINT, ctrl_c);
		// printf("%s\n", line);
	}
	exit(EXIT_SUCCESS);
}
