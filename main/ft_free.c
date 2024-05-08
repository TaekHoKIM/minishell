/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:40:38 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/08 16:12:09 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	t_token_list_free(t_token_list **head)
{
	t_token_list	*tmp;

	while ((*head) != NULL)
	{
		tmp = (*head)->next;
		free((*head)->token);
		(*head)->token = NULL;
		free((*head));
		(*head) = NULL;
		(*head) = tmp;
	}
}

void	array_2d_free(void **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}
