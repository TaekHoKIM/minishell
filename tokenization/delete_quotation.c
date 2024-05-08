/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:33:53 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/03 14:52:56 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
char	*delete_q(char *restr)
{
	char	q;
	int		i;
	char	*str;

	i = 0;
	str = restr;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			q = str[i];
			str = delete_q_helper(str, q, &i);
			if (str == NULL)
			{
				printf("delete_q\n");
				return (NULL);
			}
			else if (str[i] == '\0')
				break ;
		}
		else
			i++;
	}
	return (str);
}

char	*delete_q_helper(char *restr, char q, int *s)
{
	int		i;
	int		j;
	int		count;
	char	*str;

	i = *s + 1;
	j = *s;
	while (restr[i] != '\0')
	{
		if (restr[i] == q)
			break ;
		i++;
	}
	*s = i + 1;
	if (restr[i] == '\0')
		return (NULL);
	str = (char *)malloc((sizeof(char) * ft_strlen(restr)) - 1);
	*s = *s - 2;
	if (str == NULL)
		return (NULL);
	delete_q_helper1(str, restr, q, j);
	return (str);
}

void	delete_q_helper1(char *str, char *restr, char q, int j)
{
	int	i;
	int	count;

	i = 0;
	while (i < j)
	{
		str[i] = restr[i];
		i++;
	}
	count = 0;
	while (restr[i] != '\0')
	{
		if (restr[i] == q && count < 2)
			count++;
		else
		{
			str[j] = restr[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	free(restr);
	return ;
}
