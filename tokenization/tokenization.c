/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:32:47 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/08 19:47:32 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	tokenization(char *str, t_token_list **head)
{
	int		i;

	i = 0;
	if (quotation_check(str) == FAIL)
	{
		list_free_k(head, "quotation_check_error\n");
		return (FAIL);
	}
	while (str[i] != '\0')
	{
		if (is_space(str[i]) == FAIL)
			i = make_token(str, i, head);
		if (i == FAIL)
		{
			list_free_k(head, "make_token_error\n");
			return (FAIL);
		}
		if (str[i] == '\0')
			break ;
		else if (str[i] == '\n')
		{
			if (last_token_input(head) == FAIL)
			{
				list_free_k(head, "last_token_input_error\n");
				return (FAIL);
			}
		}
		i++;
	}
	return (token_check(head));
}

int	token_check(t_token_list **head)
{
	if (input_type(head) == FAIL)
	{
		list_free_k(head, "input_type FAIL\n");
		return (FAIL);
	}
	if (token_change(head) == FAIL)
	{
		list_free_k(head, "token_change FAIL\n");
		return (FAIL);
	}
	if (token_typing(head) == FAIL)
	{
		list_free_k(head, "token_typing FAIL\n");
		return (FAIL);
	}
	return (SUCCESS);
}

int	last_token_input(t_token_list **head)
{
	t_token_list	*temp;
	t_token_list	*new;

	new = (t_token_list *)malloc(sizeof(t_token_list) * 1);
	if (new == NULL)
		return (FAIL);
	new->type = END;
	new->token = NULL;
	new->next = NULL;
	temp = (*head);
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	return (SUCCESS);
}
