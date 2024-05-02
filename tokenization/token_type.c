/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:39:48 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/02 17:42:25 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//  ||은 오류로 띄움, | 주위 타입이 cmd 이거나 다른 거 여야 함
int	token_typing(t_token_list **head)
{
	if (syntax_check_type(head) == FAIL)
	{
		printf("syntax_check FAIL\n");
		return (FAIL);
	}
	check_cmd(head);
	check_open_redi(head);
	cmd_to_lowercase(head);
	return (SUCCESS);
}

int	input_type(t_token_list **head)
{
	int				pre_type;
	int				now_type;
	t_token_list	*now;

	pre_type = NONE;
	now = (*head);
	while (now != NULL)
	{
		if (now->type == END)
			now->type = END;
		else if (ft_strncmp(now->token, "|", 2) == SUCCESS)
			now->type = PIPE;
		else if (ft_strncmp(now->token, "||", 3) == SUCCESS)
			now->type = WRONG_TYPE;
		else if (ft_strncmp(now->token, "<", 2) == SUCCESS)
			now->type = IN_D1;
		else if (ft_strncmp(now->token, "<<", 3) == SUCCESS)
			now->type = IN_D2;
		else if (ft_strncmp(now->token, ">", 2) == SUCCESS)
			now->type = OUT_D1;
		else if (ft_strncmp(now->token, ">>", 3) == SUCCESS)
			now->type = OUT_D2;
		else if (pre_type == NONE || pre_type == PIPE || pre_type == END)
			now->type = ARG;
		else if (pre_type == ARG)
			now->type = ARG;
		else if (pre_type == IN_D1)
			now->type = IN_D1_ARG;
		else if (pre_type == IN_D2)
			now->type = IN_D2_ARG;
		else if (pre_type == OUT_D1)
			now->type = OUT_D1_ARG;
		else if (pre_type == OUT_D2)
			now->type = OUT_D2_ARG;
		else if (IN_D1_ARG <= pre_type && pre_type <= OUT_D2_ARG)
			now->type = ARG;
		else
			now->type = WRONG_TYPE;
		pre_type = now->type;
		now = now->next;
	}
	return (SUCCESS);
}

int	syntax_check_type(t_token_list **head)
{
	int				pre_type;
	int				now_type;
	t_token_list	*now;

	now = (*head);
	pre_type = NONE;
	while (now != NULL)
	{
		now_type = now->type;
		if (now_type == WRONG_TYPE)
			return (FAIL);
		else if (IN_D1 <= pre_type && pre_type <= OUT_D2)
		{
			if ((IN_D1 <= now_type && now_type <= OUT_D2) || now_type == PIPE)
				return (FAIL);
		}
		else if (pre_type == PIPE)
		{
			if (now_type == PIPE)
				return (FAIL);
		}
		pre_type = now->type;
		now = now->next;
	}
	if (now_type == PIPE || (IN_D1 <= now_type && now_type <= OUT_D2))
		return (FAIL);
	return (SUCCESS);
}

int	check_open_redi(t_token_list **head)
{
	t_token_list	*now;
	t_token_list	*in_temp;
	t_token_list	*out_temp;

	now = (*head);
	in_temp = NULL;
	out_temp = NULL;
	while (now != NULL)
	{
		if (now->type == IN_D1_ARG || now->type == IN_D2_ARG)
			in_temp = now;
		else if (now->type == OUT_D1_ARG || now->type == OUT_D2_ARG)
			out_temp = now;
		else if (now->type == PIPE)
		{
			if (in_temp != NULL)
			{
				if (in_temp->type == IN_D1_ARG)
					in_temp->type = IN_OPEN_D1;
				else if (in_temp->type == IN_D2_ARG)
					in_temp->type = IN_OPEN_D2;
			}
			if (out_temp != NULL)
			{
				if (out_temp->type == OUT_D1_ARG)
					out_temp->type = OUT_OPEN_D1;
				else if (out_temp->type == OUT_D2_ARG)
					out_temp->type = OUT_OPEN_D2;
			}
			in_temp = NULL;
			out_temp = NULL;
		}
		now = now->next;
	}
	if (in_temp != NULL)
	{
		if (in_temp->type == IN_D1_ARG)
			in_temp->type = IN_OPEN_D1;
		else if (in_temp->type == IN_D2_ARG)
			in_temp->type = IN_OPEN_D2;
	}
	if (out_temp != NULL)
	{
		if (out_temp->type == OUT_D1_ARG)
			out_temp->type = OUT_OPEN_D1;
		else if (out_temp->type == OUT_D2_ARG)
			out_temp->type = OUT_OPEN_D2;
	}
	return (SUCCESS);
}

int	check_cmd(t_token_list **head)
{
	t_token_list	*now;
	t_token_list	*temp;

	now = (*head);
	temp = NULL;
	while (now != NULL)
	{
		if (temp == NULL && now->type == ARG)
			temp = now;
		else if (now->type == PIPE || now->type == END)
		{
			if (temp != NULL)
				temp->type = CMD;
			temp = NULL;
		}
		now = now->next;
	}
	if (temp != NULL)
		temp->type = CMD;
	return (SUCCESS);
}

int	cmd_to_lowercase(t_token_list **head)
{
	t_token_list	*temp;
	char			*change_str;

	temp = (*head);
	while (temp != NULL)
	{
		if (temp->type == CMD)
		{
			change_str = ft_lowercasing(temp->token);
			if (change_str == NULL)
				return (FAIL);
			temp->token = change_str;
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
