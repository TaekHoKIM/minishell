/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:31:00 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/14 17:25:37 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_env(char *env, char **argv);

void	unset(t_envp **envp, char **argv)
{
	t_envp	*now;
	t_envp	*pre;
	t_envp	*rm;
	char	*env;

	pre = NULL;
	now = (*envp);
	printf("unset\n");
	while (now != NULL)
	{
		env = now->line;
		if (check_env(env, argv) == SUCCESS)
		{
			rm = now;
			now = now->next;
			if (pre == NULL)
				(*envp) = now;
			else
				pre->next = now;
			free(rm->line);
			free(rm);
		}
		else
			pre = now;
		now = now->next;
	}
}

static int	check_env(char *env, char **argv)
{
	int	i;
	int	len;

	i = 0;
	while (env[i] != '=')
		i++;
	len = i;
	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_strncmp(env, argv[i], len) == SUCCESS)
			if (env[len] == '=' && argv[i][len] == '\0')
				return (SUCCESS);
		i++;
	}
	return (FAIL);
}
