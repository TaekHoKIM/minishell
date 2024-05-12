/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:09:37 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/12 19:15:35 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	max;
	char	*return_ptr;

	if (s == NULL)
		return (NULL);
	max = 0;
	if (ft_strlen(s) <= (size_t)start)
		max = 0;
	else
	{
		while (s[(size_t)start + max] != '\0' && max < len)
			max++;
	}
	return_ptr = (char *)ft_malloc(sizeof(char), (max + 1));
	i = 0;
	while (i < max)
	{
		return_ptr[i] = s[(size_t)start + i];
		i++;
	}
	return_ptr[i] = '\0';
	return (return_ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*return_ptr;

	len = ft_strlen(s1);
	return_ptr = (char *)ft_malloc(sizeof(char), (len + 1));
	i = 0;
	while (s1[i] != '\0')
	{
		return_ptr[i] = s1[i];
		i++;
	}
	return_ptr[i] = '\0';
	return (return_ptr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*temp1;
	unsigned char	*temp2;

	temp1 = (unsigned char *)s1;
	temp2 = (unsigned char *)s2;
	i = 0;
	while (temp1[i] != '\0' && temp2[i] != '\0' && i < n)
	{
		if (temp1[i] > temp2[i])
			return (FAIL);
		else if (temp1[i] < temp2[i])
			return (FAIL);
		i++;
	}
	if (i == n)
		return (SUCCESS);
	if (temp1[i] > temp2[i])
		return (FAIL);
	else if (temp1[i] < temp2[i])
		return (FAIL);
	return (SUCCESS);
}
