/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 23:39:28 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/20 19:19:42 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_str(char *str, int start, int len)
{
	char	*re_str;
	int		i;

	re_str = (char *)ft_malloc(sizeof(char), (ft_strlen(str) - len + 1));
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
	int		cha_len;
	int		set[2];

	cha_len = ft_strlen(change_str);
	re_str = (char *)ft_malloc(sizeof(char),
			(ft_strlen(str) + cha_len + 1 - len));
	i = 0;
	while (i < start)
	{
		re_str[i] = str[i];
		i++;
	}
	set[0] = start;
	set[1] = len;
	change_str1(str, re_str, change_str, set);
	free(str);
	return (re_str);
}

void	change_str1(char *str, char *re_str, char *change_str, int set[2])
{
	int	i;
	int	j;

	j = set[0];
	i = 0;
	while (change_str[i] != '\0')
	{
		re_str[j] = change_str[i];
		j++;
		i++;
	}
	i = set[0] + set[1];
	while (str[i] != '\0')
	{
		re_str[j] = str[i];
		j++;
		i++;
	}
	re_str[j] = '\0';
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
				re_str = ft_substr(cmp_str, (strlen + 1),
						(ft_strlen(cmp_str) - (strlen + 1)));
				return (re_str);
			}
		}
		temp = temp->next;
	}
	return (NULL);
}
