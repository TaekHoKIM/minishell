/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 23:39:28 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/02 17:20:38 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_str(char *str, int start, int len)
{
	char	*re_str;
	int		i;

	re_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (re_str == NULL)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (i < start)
	{
		re_str[i] = str[i];
		i++;
	}
	i = i + len;
	while (str[i] != '\0')
	{
		re_str[start] = str[i];
		start++;
		i++;
	}
	re_str[start] = '\0';
	free(str);
	return (re_str);
}

char	*change_str(char *str, int start, char *change_str, int len)
{
	char	*re_str;
	int		i;
	int		j;
	int		cha_len;

	cha_len = ft_strlen(change_str);
	re_str = (char *)malloc(sizeof(char) *(ft_strlen(str) + cha_len + 1 - len));
	if (re_str == NULL)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (i < start)
	{
		re_str[i] = str[i];
		i++;
	}
	change_str1(str, re_str, change_str, start, len);
	free(str);
	return (re_str);
}

void	change_str1(char *str, char *re_str, char *change_str, int start, int len)
{
	int	i;
	int	j;

	j = start;
	i = 0;
	while (change_str[i] != '\0')
	{
		re_str[j] = change_str[i];
		j++;
		i++;
	}
	i = start + len;
	while (str[i] != '\0')
	{
		re_str[j] = str[i];
		j++;
		i++;
	}
	re_str[j] = '\0';
}
