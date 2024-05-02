/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:14:36 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/02 21:15:21 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_malloc(size_t size, size_t cnt)
{
	void	*tmp;

	tmp = malloc(sizeof(size) * cnt);
	if (tmp == NULL)
		exit(EXIT_FAILURE);
	return (tmp);
}

void	t_token_list_free(t_token_list *head)
{
	t_token_list	*tmp;
	
	while (head != NULL)
	{
		tmp = head->next;
		free(head->token);
		free(head);
		head = tmp;
	}
}

void	set_envp(t_envp **env, char **envp)
{
	t_envp	*new;
	t_envp	*tmp;
	int		i;

	i = 0;
	while(envp[i] != NULL)
	{
		new = ft_malloc(sizeof(tmp), 1);
		new->line = ft_strdup(envp[i]);
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
