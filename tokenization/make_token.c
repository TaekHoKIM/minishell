/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:56:48 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/08 15:27:16 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int	make_token(char *str, int start, t_token_list **head)
{
	int		i;
	int		flag;
	char	q;

	flag = OFF;
	q = str[start];
	if (q == '\'' || q == '\"')
		flag = ON;
	else if (q == '<' || q == '>' || q == '|')
	{
		i = make_token_sub(str, start, head);
		if (i == FAIL)
			return (FAIL);
		return (i);
	}
	i = make_token_sub1(str, start, q, flag);
	if (str_to_token(str, start, i, head) == FAIL)
		return (FAIL);
	if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		i--;
	return (i);
}

int	make_token_sub(char *str, int start, t_token_list **head)
{
	char	q;
	char	p;

	q = str[start];
	p = str[start + 1];
	if ((q == '<' && p == '<') || (q == '>' && p == '>'))
	{
		if (str_to_token(str, start, start + 2, head) == FAIL)
			return (FAIL);
		return (start + 1);
	}
	else if ((q == '|' && p == '|'))
	{
		if (str_to_token(str, start, start + 2, head) == FAIL)
			return (FAIL);
		return (start + 1);
	}
	else if (q == '|' || (q == '<') || (q == '>'))
	{
		if (str_to_token(str, start, start + 1, head) == FAIL)
			return (FAIL);
		return (start);
	}
	return (FAIL);
}

int	make_token_sub1(char *str, int start, int q, int flag)
{
	int	i;

	i = start + 1;
	while (str[i] != '\0')
	{
		if (str[i] == q && flag == ON)
			flag = OFF;
		else if ((str[i] == '\'' || str[i] == '\"') && flag == OFF)
		{
			q = str[i];
			flag = ON;
		}
		else if (flag == OFF && is_space(str[i]) == SUCCESS)
			break ;
		else if (flag == OFF && ((str[i] == '<' || (str[i] == '>')
					|| str[i] == '|')))
			break ;
		i++;
	}
	return (i);
}

int	str_to_token(char *str, int start, int i, t_token_list **head)
{
	char	*re_str;

	re_str = ft_substr(str, start, i - start);
	if (re_str == NULL)
	{
		return (FAIL);
	}
	if (input_token(re_str, head) == FAIL)
	{
		free(re_str);
		return (FAIL);
	}
	return (SUCCESS);
}

int	input_token(char *str, t_token_list **head)
{
	t_token_list	*new;
	t_token_list	*temp;

	new = (t_token_list *)malloc(sizeof(t_token_list) * 1);
	if (new == NULL)
		return (FAIL);
	new->token = str;
	new->next = NULL;
	if ((*head) == NULL)
	{
		(*head) = new;
	}
	else
	{
		temp = (*head);
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
	return (SUCCESS);
}
