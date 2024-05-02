/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:32:47 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/02 17:32:53 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	tokenization(char *str, t_token_list **head)
{
	int		i;

	i = 0;
	// ",' 확인
	if (quotation_check(str) == FAIL)
	{
		printf("quotation_check_error\n");
		return (FAIL);
	}
	while (str[i] != '\0')
	{
		if (is_space(str[i]) == FAIL)
			i = make_token(str, i, head);
		if (i == FAIL)
		{
			printf("make_token_error\n");
			list_free(head);
			return (FAIL);
		}
		if (str[i] == '\0')
			break ;
		else if (str[i] == '\n')
		{
			if (last_token_input(head) == FAIL)
			{
				printf("last_token_input_error\n");
				list_free(head);
				return (FAIL);
			}
		}
		i++;
	}
	if (token_typing(head) == FAIL)
	{
		printf("input_type FAIL\n");
		return (FAIL);
	}
	return (SUCCESS);
}

int	token_change(t_token_list **head)
{
	char			*re_str;
	t_token_list	*now;

	now = (*head);
	if (now == NULL)
		return (FAIL);
	while (now != NULL)
	{
		if (now->type != END)
		{
			re_str = now->token;
			re_str = change_env(re_str);
			if (re_str == NULL)
				return (FAIL);
			re_str = delete_q(re_str);
			if (re_str == NULL)
				return (FAIL);
			now->token = re_str;
		}
		now = now->next;
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
