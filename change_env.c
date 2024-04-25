/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:09:35 by taekhkim          #+#    #+#             */
/*   Updated: 2024/04/26 00:33:06 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_env(char *str)
{
	int		i;
	int		flag;
	char	*re_str;

	i = 0;
	flag = ON;
	re_str = str;
	while (re_str[i] != '\0')
	{
		if (change_env_flag(re_str[i], &flag) == ON)
		{
			re_str = change_env_sub(re_str, &i);
			if (re_str == NULL)
				return (NULL);
		}
		i++;
	}
	return (re_str);
}

char	*change_env_sub(char *str, int	*index)
{
	int		i;
	int		j;
	char	*restr;
	char	*temp_str;
	char	*env_str;

	i = *index;
	restr = str;
	j = check_special_char(restr, i);
	if (j != 1)
	{
		temp_str = ft_substr(restr, i + 1, j - 1);
		if (temp_str == NULL)
		{
			free(restr);
			return (NULL);
		}
		i = change_env_sub1(&restr, temp_str, i, j);
		free(temp_str);
		if (i == FAIL)
			return (NULL);
		*index = i;
	}
	return (restr);
}

int	change_env_sub1(char **restr, char *temp_str, int i, int j)
{
	int		idx;
	char	*env_str;

	env_str = getenv(temp_str);
	if (env_str != NULL)
		env_str = ft_strdup(env_str);
	idx = i;
	if (env_str == NULL)
	{
		*restr = remove_str(*restr, idx, j);
		idx--;
	}
	else
	{
		*restr = change_str(*restr, idx, env_str, j);
		idx = idx + ft_strlen(env_str) - 1;
	}
	free(env_str);
	if (restr == NULL)
		return (FAIL);
	return (idx);
}

int	change_env_flag(char c, int *flag)
{
	if (c == '\'' && *flag == ON)
		*flag = OFF;
	else if (c == '\'' && *flag == OFF)
		*flag = ON;
	else if (c == '\"' && *flag == ON)
		*flag = DQ;
	else if (c == '\"' && *flag == DQ)
		*flag = ON;
	else if (c == '$' && (*flag == ON || *flag == DQ))
		return (ON);
	return (OFF);
}

int	check_special_char(char *restr, int i)
{
	int		j;
	char	c;

	j = 1;
	c = restr[i + j];
	if (!(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_'))
		return (j);
	j++;
	c = restr[i + j];
	while ((('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || (c == '_')
			|| ('0' <= c && c <= '9')))
		{
			j++;
			c = restr[i + j];
		}
	return (j);
}
