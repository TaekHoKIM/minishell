/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:32:47 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/02 15:09:53 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		make_token_sub(char *str, int start, t_token_list **head);
void	last_token_input(t_token_list **head);

int	tokenization(char *str, t_token_list **head)
{
	int		i;

	i = 0;
	if (quotation_check(str) == FAIL)
	{
		printf("quotation_error\n");
		return (FAIL);
	}
	while (str[i] != '\0')
	{
		if (is_space(str[i]) == FAIL)
			i = make_token(str, i, head);
		if (i == FAIL)
		{
			printf("fail\n");
			list_free(head);
			exit(EXIT_FAILURE);
		}
		if (str[i] == '\0')
			break ;
		else if (str[i] == '\n')
			last_token_input(head);
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
	q = str[start];
	// 모든 공백(\n 포함)이랑 << < > >> | 으로 구분해줘야 함
	if (q == '\'' || q == '\"')
		flag = ON;
	else if (q == '<' || q == '>' || q == '|')
	{
		i = make_token_sub(str, start, head);
		if (i == FAIL)
			return (FAIL);
		return (i);
	}
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
		else if (flag == OFF && (str[i] == '<' || str[i] == '>' || str[i] == '|'))
		{
			i--;
			break ;
		}
		i++;
	}
	if (str_to_token(str, start, i, head) == FAIL)
		return (FAIL);
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
	if (str[i] == '\n')
		last_token_input(head);
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
		if (now->type != END)
		{
			re_str = now->token;
			re_str = change_env(re_str);
			re_str = delete_q(re_str);
			now->token = re_str;
		}
		now = now->next;
	}
	return (SUCCESS);
}

void	last_token_input(t_token_list **head)
{
	t_token_list	*temp;
	t_token_list	*new;

	new = (t_token_list *)malloc(sizeof(t_token_list) * 1);
	new->type = END;
	new->token = NULL;
	new->next = NULL;
	temp = (*head);
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	return ;
}
