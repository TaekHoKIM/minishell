/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:59:59 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/08 19:46:53 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_wordcount(char const *s, char c)
{
	int	flag;
	int	cnt;

	flag = 0;
	cnt = 0;
	while (*s != '\0')
	{
		if (flag == 0 && *s != c)
		{
			cnt++;
			flag = 1;
		}
		else if (*s == c)
			flag = 0;
		s++;
	}
	return (cnt);
}

static char	*ft_wordcut(char const **s, char c)
{
	char	*temp;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while ((*s)[len] != c && (*s)[len] != '\0')
		len++;
	temp = ft_malloc(sizeof(char), (len + 1));
	while (**s != c && **s != '\0')
	{
		temp[i] = **s;
		i++;
		(*s)++;
	}
	temp[i] = '\0';
	return (temp);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	i;

	words = ft_malloc(sizeof(char *), (ft_wordcount(s, c) + 1));
	i = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			words[i] = ft_wordcut(&s, c);
			i++;
		}
		else
			s++;
	}
	words[i] = NULL;
	return (words);
}