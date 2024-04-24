/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:33:53 by taekhkim          #+#    #+#             */
/*   Updated: 2024/04/22 17:20:13 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_q(char *restr)
{
	char	q;
	int		i;
	char	*str;

	i = 0;
	while (restr[i] != '\0')
	{
		if (restr[i] == '\'' || restr[i] == '\"')
		{
			q = restr[i];
			break ;
		}
		i++;
	}
	str = delete_q_helper(restr, q);
	if (str == NULL)
	{
		free(restr);
		return (NULL);
	}
	return (str);
}

char	*delete_q_helper(char *restr, char q)
{
	int		i;
	int		j;
	int		count;
	char	*str;

	count = 0;
	i = 0;
	while (restr[i] != '\0')
	{
		if (restr[i] == q)
			count++;
		i++;
	}
	if (count % 2 == 1)
		return (NULL);
	str = (char *)malloc((sizeof(char) * ft_strlen(restr)) - count + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (restr[i] != '\0')
	{
		if (restr[i] == q)
			i++;
		else
		{
			str[j] = restr[i];
			j++;
			i++;
		}
	}
	free(restr);
	return (str);
}
