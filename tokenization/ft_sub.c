/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:28:51 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/03 14:14:00 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_lowercasing(char *cmd)
{
	int		i;
	int		len;
	char	*lower_str;

	len = ft_strlen(cmd);
	lower_str = (char *)malloc(sizeof(char) * (len + 1));
	if (lower_str == NULL)
		return (NULL);
	i = 0;
	while (cmd[i] != '\0')
	{
		if ('A' <= cmd[i] && cmd[i] <= 'Z')
			lower_str[i] = cmd[i] + 32;
		else
			lower_str[i] = cmd[i];
		i++;
	}
	lower_str[i] = '\0';
	free(cmd);
	return (lower_str);
}
