/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:09:35 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/12 19:32:30 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*change_env(char *str, t_envp *env)
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
			re_str = change_env_sub(re_str, &i, env);
		}
		i++;
	}
	return (re_str);
}

char	*change_env_sub(char *str, int	*index, t_envp *env)
{
	int		set[2];
	char	*restr;
	char	*temp_str;
	char	*env_str;

	set[0] = *index;
	restr = str;
	set[1] = check_special_char(restr, set[0]);
	if (set[1] != 1)
	{
		temp_str = ft_substr(restr, set[0] + 1, set[1] - 1);
		set[0] = change_env_sub1(&restr, temp_str, set, env);
		free(temp_str);
		*index = set[0];
	}
	return (restr);
}

int	change_env_sub1(char **restr, char *temp_str, int set[2], t_envp *env)
{
	int		idx;
	char	*env_str;

	env_str = user_getenv(temp_str, env);
	idx = set[0];
	if (env_str == NULL)
	{
		*restr = remove_str(*restr, idx, set[1]);
		idx--;
	}
	else
	{
		*restr = change_str(*restr, idx, env_str, set[1]);
		idx = idx + ft_strlen(env_str) - 1;
	}
	free(env_str);
	if (idx == -1)
		return (0);
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
	while ((('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')
			|| (c == '_') || ('0' <= c && c <= '9')))
	{
		j++;
		c = restr[i + j];
	}
	return (j);
}
