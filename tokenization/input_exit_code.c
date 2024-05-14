/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_exit_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:58:09 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/14 15:23:51 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*input_exit_code(char *str, int exit_code, int *i)
{
	int		index;
	int		re_str_i;
	char	*exit_str;
	char	*re_str;

	exit_str = ft_itoa(exit_code);
	re_str = (char *)ft_malloc(sizeof(char), ((ft_strlen(str) - 2)
				+ (ft_strlen(exit_str) + 1)));
	index = 0;
	while (index < *i)
	{
		re_str[index] = str[index];
		index++;
	}
	input_exit_code_sub(str, exit_str, re_str, *i);
	(*i) = (*i) + ft_strlen(exit_str) - 1;
	free(str);
	return (re_str);
}

void	input_exit_code_sub(char *str, char *exit_str, char *re_str, int i)
{
	int		str_i;
	int		re_str_i;
	int		temp;

	re_str_i = i;
	str_i = i + 2;
	temp = 0;
	while (temp < ft_strlen(exit_str))
	{
		re_str[re_str_i] = exit_str[temp];
		temp++;
		re_str_i++;
	}
	while (str[str_i] != '\0')
	{
		re_str[re_str_i] = str[str_i];
		re_str_i++;
		str_i++;
	}
	re_str[re_str_i] = '\0';
}
