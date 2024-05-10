/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check_and_exec.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:36:12 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/11 03:06:35 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i + 1] == '\0' && s2[i + 1] == '\0')
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}

void	builtin_check_and_exec(t_token_list *head, t_envp *envp, t_info *info)
{
	t_token_list	*tmp;

	tmp = head;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (tmp->type == CMD)
		{
			// if (ft_strcmp(tmp->token, "echo") == SUCCESS)
				
			if (ft_strcmp(tmp->token, "cd") == SUCCESS)
				change_dir(head, envp, info);
			// else if (ft_strcmp(tmp->token, "pwd") == SUCCESS)
				
			// else if (ft_strcmp(tmp->token, "export") == SUCCESS)
				
			// else if (ft_strcmp(tmp->token, "unset") == SUCCESS)
				
			// else if (ft_strcmp(tmp->token, "env") == SUCCESS)
				
			// else if (ft_strcmp(tmp->token, "exit") == SUCCESS)
				
		}
		tmp = tmp->next;
	}
}
