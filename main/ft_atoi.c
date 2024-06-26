/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:47:27 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/23 23:30:29 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *str, int *check)
{
	long long	minus;
	long long	result;

	minus = 1;
	result = 0;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	while ('0' <= *str && *str <= '9' && *str != '\0')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	if (*str != '\0')
		*check = FAIL;
	else
		*check = SUCCESS;
	return ((int)(result * minus));
}
