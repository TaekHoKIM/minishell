/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:14:41 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/28 16:56:36 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"

int	g_exit_code;

static void	make_home(t_envp **envp, t_info *info)
{
	t_envp	*tmp;

	info->first_home = NULL;
	tmp = *envp;
	while (tmp != NULL)
	{
		if (tmp->line[0] == 'H' && tmp->line[1] == 'O'
			&& tmp->line[2] == 'M' && tmp->line[3] == 'E'
			&& tmp->line[4] == '=')
			info->first_home = ft_strdup(tmp->line + 5);
		tmp = tmp->next;
	}
}

static void	initial_set(t_token_list **head, t_info *info,
	t_envp **env, char **envp)
{
	info->argv = NULL;
	info->cmd_cnt = 0;
	info->envp = NULL;
	info->here_doc_cnt = 0;
	info->home_dir = NULL;
	info->i_fd = STDIN_FILENO;
	info->last_child_pid = 0;
	info->o_fd = STDOUT_FILENO;
	info->path = NULL;
	info->pid = NULL;
	info->pipe_cnt = 0;
	info->pipefd = NULL;
	g_exit_code = 0;
	set_terminal_not_print();
	bagic_set_parent_signal();
	*head = NULL;
	*env = NULL;
	set_envp(env, envp);
	make_home(env, info);
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
	initial_set(&head, &info, &env, envp);
	while (1)
	{
		line = readline("minishell % ");
		if (line == NULL)
			ctrl_d_print_exit();
		add_history(line);
		if (tokenization(line, &head, env, g_exit_code) == FAIL)
			continue ;
		if (here_doc_preprocessor(head, &info, env) != FAIL)
			exec_process(head, &env, &info);
		finish_set(&head, &info);
	}
	exit(EXIT_SUCCESS);
}
