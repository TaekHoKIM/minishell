/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:50:48 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/02 21:00:51 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
// 	result = malloc(sizeof(char) * len + 1);
// 	if (result == NULL)
// 		exit(EXIT_FAILURE);
// 	result[len] = '\0';
// 	while (str[i] != '\0')
// 	{
// 		result[i] = str[i];
// 		i++;
// 	}
// 	return (result);
// }