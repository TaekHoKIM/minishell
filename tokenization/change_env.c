/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:09:35 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/10 15:08:04 by taekhkim         ###   ########.fr       */
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
			if (re_str == NULL)
				return (NULL);
		}
		i++;
	}
	return (re_str);
}

char	*change_env_sub(char *str, int	*index, t_envp *env)
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
		i = change_env_sub1(&restr, temp_str, i, j, env);
		free(temp_str);
		if (i == FAIL)
			return (NULL);
		*index = i;
	}
	return (restr);
}

int	change_env_sub1(char **restr, char *temp_str, int i, int j, t_envp *env)
{
	int		idx;
	char	*env_str;

	env_str = user_getenv(temp_str, env);
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
	if (idx == -1)
		return (0);
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

char	*user_getenv(char *str, t_envp *env)
{
	int		strlen;
	char	*cmp_str;
	char	*re_str;
	t_envp	*temp;

	strlen = ft_strlen(str);
	temp = env;
	while (temp != NULL)
	{
		cmp_str = temp->line;
		if (ft_strncmp(str, cmp_str, strlen) == SUCCESS)
		{
			if (cmp_str[strlen] == '=')
			{
				re_str = ft_substr(cmp_str, strlen + 1, ft_strlen(cmp_str) - (strlen + 1));
				if (re_str == NULL)
					return (NULL);
				return (re_str);
			}
		}
		temp = temp->next;
	}
	return (NULL);
}
