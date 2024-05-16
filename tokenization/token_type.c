/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:39:48 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/16 16:32:03 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_typing(t_token_list **head)
{
	if (syntax_check_type(head) == FAIL)
		return (FAIL);
	check_cmd(head);
	check_open_redi(head);
	// remove_token(head);
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
		else
			input_type_sub(now, pre_type);
		pre_type = now->type;
		now = now->next;
	}
	return (SUCCESS);
}

void	input_type_sub(t_token_list *now, int pre_type)
{
	if (ft_strncmp(now->token, ">", 2) == SUCCESS)
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
		else if (pre_type == PIPE && now_type == PIPE)
			return (FAIL);
		pre_type = now->type;
		now = now->next;
	}
	if (now_type == PIPE || (IN_D1 <= now_type && now_type <= OUT_D2))
		return (FAIL);
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
