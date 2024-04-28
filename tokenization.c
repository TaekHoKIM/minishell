/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:32:47 by taekhkim          #+#    #+#             */
/*   Updated: 2024/04/28 21:18:21 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenization(char *str, t_token_list **head)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			i = make_token(str, i, head);
		if (i == FAIL)
		{
			printf("fail\n");
			list_free(head);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (token_typing(head) == FAIL)
	{
		printf("input_type FAIL\n");
	}
	return (SUCCESS);
}

int	make_token(char *str, int start, t_token_list **head)
{
	int		i;
	int		flag;
	char	q;

	flag = OFF;
	if (quotation_check(str) == FAIL)
		return (FAIL);
	q = str[start];
	if (q == '\'' || q == '\"')
		flag = ON;
	else if (q != '\0' && ((q == '<' && str[start + 1] == '<') || (q == '>' && str[start + 1] == '>')))
	{
		str_to_token(str, start, start + 2, head);
		return (start + 1);
	}
	else if (q != '\0' && (q == '|' && str[start + 1] == '|'))
	{
		str_to_token(str, start, start + 2, head);
		return (start + 1);
	}
	else if (q == '|' || (q == '<') || (q == '>'))
	{
		str_to_token(str, start, start + 1, head);
		return (start);
	}
	i = start + 1;
	while (!((str[i] == ' ' || str[i] == '\0' || str[i] == '|' || str[i] == '<' || str[i] == '>') && flag == OFF))
	{
		if ((str[i] == q) && flag == ON)
			flag = OFF;
		else if ((str[i] == '\"' || str[i] == '\'') && flag == OFF)
		{
			flag = ON;
			q = str[i];
		}
		i++;
	}
	if (str_to_token(str, start, i, head) == FAIL)
		return (FAIL);
	if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
	{
		str_to_token(str, i, i + 2, head);
		return (i + 1);
	}
	else if (q != '\0' && (q == '|' && str[i + 1] == '|'))
	{
		str_to_token(str, i, i + 2, head);
		return (i + 1);
	}
	else if (str[i] == '|' || (str[i] == '<') || (str[i] == '>'))
	{
		str_to_token(str, i, i + 1, head);
		return (i);
	}
	return (i - 1);
}

int	input_token(char *str, t_token_list **head)
{
	t_token_list	*new;
	t_token_list	*temp;

	new = (t_token_list *)malloc(sizeof(t_token_list) * 1);
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

int	quotation_check(char *str)
{
	int		i;
	int		count;
	char	q;

	i = 0;
	q = ' ';
	while (str[i] != '\0')
	{
		if (q == ' ' && (str[i] == '\'' || str[i] == '\"'))
		{
			q = str[i];
		}
		else if (str[i] == q)
		{
			q = ' ';
		}
		i++;
	}
	if (q == ' ')
		return (SUCCESS);
	else
	{
		printf("syntax error\n");
		return (FAIL);
	}
}

int	str_to_token(char *str, int start, int i, t_token_list **head)
{
	char	*re_str;

	re_str = ft_substr(str, start, i - start);
	if (re_str == NULL)
	{
		printf("malloc error\n");
		return (FAIL);
	}
	input_token(re_str, head);
	if (input_type(head) == FAIL)
		printf("input_type FAIL\n");
	if (token_change(head) == FAIL)
		printf("token_change FAIL\n");
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
		re_str = now->token;
		re_str = change_env(re_str);
		re_str = delete_q(re_str);
		now->token = re_str;
		now = now->next;
	}
	return (SUCCESS);
}
