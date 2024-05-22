/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:58:36 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/22 16:58:14 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	remove_token(t_token_list **head)
{
	t_token_list	*now_t;
	t_token_list	*rm_t;

	now_t = (*head);
	while (now_t != NULL)
	{
		if (now_t->token != NULL && ft_strlen(now_t->token) == 0)
		{
			rm_t = now_t;
			free(rm_t->token);
			now_t = now_t->next;
			free(rm_t);
		}
		else
			break ;
	}
	if (now_t != (*head))
		(*head) = now_t;
	remove_token_sub(now_t);
	return (SUCCESS);
}

void	remove_token_sub(t_token_list *now)
{
	t_token_list	*pre_t;
	t_token_list	*now_t;
	t_token_list	*rm_t;

	if (now == NULL)
		return ;
	now_t = now;
	pre_t = now_t;
	now_t = now_t->next;
	while (now_t != NULL)
	{
		if (now_t->token != NULL && ft_strlen(now_t->token) == 0)
		{
			rm_t = now_t;
			free(rm_t->token);
			now_t = now_t->next;
			pre_t->next = now_t;
			free(rm_t);
		}
		else
		{
			pre_t = now_t;
			now_t = now_t->next;
		}
	}
}
