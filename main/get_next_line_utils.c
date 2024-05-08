/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:50:48 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/08 15:22:14 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	find_enter(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (FAIL);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}

// char	*ft_strdup(char *str)
// {
// 	size_t	len;
// 	size_t	i;
// 	char	*result;

// 	len = ft_strlen(str);
// 	i = 0;
// 	result = ft_malloc(sizeof(char), len + 1);
// 	result[len] = '\0';
// 	while (str[i] != '\0')
// 	{
// 		result[i] = str[i];
// 		i++;
// 	}
// 	return (result);
// }