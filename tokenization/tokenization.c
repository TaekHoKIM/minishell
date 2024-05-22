/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:32:47 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/22 16:58:54 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tokenization(char *str, t_token_list **head, t_envp *env, int exit_code)
{
	int		i;

	i = 0;
	if (quotation_check(str) == FAIL)
	{
		free(str);
		printf("Quotation Error\n");
		return (FAIL);
	}
	while (str[i] != '\0')
	{
		if (is_space(str[i]) == FAIL)
			i = make_token(str, i, head);
		if (str[i] == '\0')
			break ;
		else if (str[i] == '\n')
		{
			last_token_input(head);
		}
		i++;
	}
	free(str);
	return (token_check(head, env, exit_code));
}

int	token_check(t_token_list **head, t_envp *env, int exit_code)
{
	input_type(head);
	token_change_env(head, env, exit_code);
	remove_token(head);
	input_type(head);
	token_change_qutation(head);
	if (token_typing(head) == FAIL)
	{
		list_free_k(head, "Syntax Error\n");
		return (FAIL);
	}
	return (SUCCESS);
}

int	last_token_input(t_token_list **head)
{
	t_token_list	*temp;
	t_token_list	*new;

	new = (t_token_list *)ft_malloc(sizeof(t_token_list), 1);
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
