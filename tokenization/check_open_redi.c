/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_open_redi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:54:53 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/12 18:55:42 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			check_open_redi_mid(&in_temp, &out_temp);
		now = now->next;
	}
	check_open_redi_last(&in_temp, &out_temp);
	return (SUCCESS);
}

void	check_open_redi_mid(t_token_list **in_temp, t_token_list **out_temp)
{
	if ((*in_temp) != NULL)
	{
		if ((*in_temp)->type == IN_D1_ARG)
			(*in_temp)->type = IN_OPEN_D1;
		else if ((*in_temp)->type == IN_D2_ARG)
			(*in_temp)->type = IN_OPEN_D2;
	}
	if ((*out_temp) != NULL)
	{
		if ((*out_temp)->type == OUT_D1_ARG)
			(*out_temp)->type = OUT_OPEN_D1;
		else if ((*out_temp)->type == OUT_D2_ARG)
			(*out_temp)->type = OUT_OPEN_D2;
	}
	(*in_temp) = NULL;
	(*out_temp) = NULL;
}

void	check_open_redi_last(t_token_list **in_temp, t_token_list **out_temp)
{
	if ((*in_temp) != NULL)
	{
		if ((*in_temp)->type == IN_D1_ARG)
			(*in_temp)->type = IN_OPEN_D1;
		else if ((*in_temp)->type == IN_D2_ARG)
			(*in_temp)->type = IN_OPEN_D2;
	}
	if ((*out_temp) != NULL)
	{
		if ((*out_temp)->type == OUT_D1_ARG)
			(*out_temp)->type = OUT_OPEN_D1;
		else if ((*out_temp)->type == OUT_D2_ARG)
			(*out_temp)->type = OUT_OPEN_D2;
	}
}
