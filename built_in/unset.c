/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:31:00 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/20 19:21:31 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset_env(t_envp **envp, t_envp *rm)
{
	t_envp	*pre;
	t_envp	*now;

	if (rm == NULL)
		return ;
	pre = NULL;
	now = (*envp);
	while (now != NULL)
	{
		if (now == rm)
		{
			if (pre == NULL)
				(*envp) = now->next;
			else
				pre->next = now->next;
			free(now->line);
			free(now);
			return ;
		}
		else
			pre = now;
		now = now->next;
	}
}

static t_envp	*check_env(t_envp **envp, char *argv)
{
	t_envp	*tmp;
	int		len;

	tmp = *envp;
	while (tmp != NULL)
	{
		len = 0;
		while (tmp->line[len] != '=')
			len++;
		if (ft_strncmp(tmp->line, argv, len) == SUCCESS)
			if (argv[len] == '\0')
				return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static int	check_unset_argv(char *argv)
{
	int	idx;

	idx = 0;
	while (argv[idx] != '\0')
	{
		if (!(('A' <= argv[idx] && argv[idx] <= 'Z')
				|| ('a' <= argv[idx] && argv[idx] <= 'z')
				|| ('0' <= argv[idx] && argv[idx] <= '9')))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(argv, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (FAIL);
		}
		idx++;
	}
	return (SUCCESS);
}

int	unset(t_token_list *head, t_envp **envp, t_info *info)
{
	t_envp	*rm;
	int		i;

	if (info->pipe_cnt != 0)
		return (FAIL);
	if (*envp == NULL)
		return (SUCCESS);
	info->exit_code = 0;
	i = 1;
	argv_set(head, info);
	while (info->argv[i] != NULL)
	{
		if (check_unset_argv(info->argv[i]) == SUCCESS)
		{
			rm = check_env(envp, info->argv[i]);
			unset_env(envp, rm);
		}
		i++;
	}
	return (SUCCESS);
}
