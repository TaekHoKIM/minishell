/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:49:52 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/08 19:46:53 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc_file_unlink(int here_doc_cnt)
{
	int		cnt;
	char	*filename;
	char	*tmp;
	
	cnt = 1;
	while (cnt <= here_doc_cnt)
	{
		tmp = ft_itoa(cnt);
		filename = ft_strjoin(".temp", tmp);
		unlink(filename);
		free(tmp);
		free(filename);
		cnt++;
	}
}

int	ft_limiter_check(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (NO_LIMITER);
		i++;
	}
	if (str1[i] == '\n' && str1[i + 1] == '\0' && str2[i] == '\0')
		return (YES_LIMITER);
	return (NO_LIMITER);
}
