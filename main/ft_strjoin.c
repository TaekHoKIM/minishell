/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:59:51 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/12 18:00:23 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i + 1 < size && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (size != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

static size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	i = d_len;
	while (i + 1 < size && src[i - d_len] != '\0')
	{
		dst[i] = src[i - d_len];
		i++;
	}
	if (size != 0)
		dst[i] = '\0';
	if (d_len < size)
		return (d_len + s_len);
	return (s_len + size);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*tmp;

	len1 = 0;
	len2 = 0;
	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	tmp = ft_malloc(sizeof(char), (len1 + len2 + 1));
	ft_strlcpy(tmp, s1, len1 + 1);
	ft_strlcat(tmp, s2, len1 + len2 + 1);
	return (tmp);
}
