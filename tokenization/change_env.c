/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:09:35 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/08 19:48:07 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	// 여기에서 getenv가 아니라 다른 거를 사용해야 됨 함수 변환 필요 + 인자로 env list 필요
	if (env_str != NULL)
		env_str = ft_strdup(env_str);
	// 여기까지 고려해서 env 함수 만들기
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
