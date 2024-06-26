/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:54:10 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/17 21:42:05 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_envp(t_envp **env, char **envp)
{
	t_envp	*new;
	t_envp	*tmp;
	int		i;

	i = 0;
	if (envp == NULL)
		return ;
	while (envp[i] != NULL)
	{
		new = ft_malloc(sizeof(t_envp), 1);
		new->line = ft_strdup(envp[i]);
		new->key = ENV;
		new->next = NULL;
		if (i == 0)
			*env = new;
		else
		{
			tmp = *env;
			while ((tmp)->next != NULL)
				tmp = tmp->next;
			tmp->next = new;
		}
		i++;
	}
}
