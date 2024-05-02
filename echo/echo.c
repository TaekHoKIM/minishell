/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:20:36 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/02 16:01:47 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(char **argv)	// 종료코드 정상 0 / 비정상 1
{
	int	i;
	int	len;
	int	n_option;

	i = 0;
	while (argv[i] != NULL)
		i++;
	len = i;
	if (ft_strncmp(argv[0], "echo", 5) == FAIL)
		return (1);
	i = 1;
	n_option = OFF;
	while (argv[i] != NULL)
	{
		if (ft_strncmp(argv[i], "-n", 3) == FAIL)
			break ;
		else if (ft_strncmp(argv[i], "-n", 3) == SUCCESS)
			n_option = ON;
		i++;
	}
	while (argv[i] != NULL)
	{
		printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_option == OFF)
		printf("\n");
	return (0);
}