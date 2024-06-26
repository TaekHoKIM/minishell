/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:03:36 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/20 19:20:00 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotation_check(char *str)
{
	int		i;
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
	return (FAIL);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\v' || c == '\f')
		return (SUCCESS);
	else if (c == '\r' || c == '\n' || c == '\t')
		return (SUCCESS);
	return (FAIL);
}

void	list_free_k(t_token_list **head, char *error_msg)
{
	t_token_list	*temp;
	t_token_list	*remove;

	temp = *head;
	if (temp == NULL)
		return ;
	while (temp != NULL)
	{
		remove = temp;
		temp = temp->next;
		if (remove->token != NULL)
			free(remove->token);
		free(remove);
	}
	printf("%s", error_msg);
	(*head) = NULL;
	return ;
}
