/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 19:01:34 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/12 18:11:24 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	put_digit(char *temp, long long n, size_t cnt)
{
	if (n < 0)
	{
		temp[0] = '-';
		n *= -1;
	}
	while (n)
	{
		temp[--cnt] = n % 10 + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*temp;
	size_t	cnt;
	int		t_n;

	cnt = 0;
	t_n = n;
	while (t_n)
	{
		t_n /= 10;
		cnt++;
	}
	if (n < 0)
		cnt++;
	if (n == 0)
		return (ft_strdup("0"));
	temp = ft_malloc(sizeof(char), (cnt + 1));
	temp[cnt] = '\0';
	put_digit(temp, (long long)n, cnt);
	return (temp);
}
