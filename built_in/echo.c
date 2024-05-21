/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:20:36 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/21 17:58:55 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	echo_sub(char **argv, int *i, int *n_option);

// 종료코드 정상 0 / 비정상 1
void	echo(char **argv)
{
	int	i;
	int	len;
	int	n_option;

	i = 0;
	while (argv[i] != NULL)
		i++;
	len = i;
	if (ft_strncmp(argv[0], "echo", 5) == FAIL)
		exit(EXIT_FAILURE);
	n_option = OFF;
	echo_sub(argv, &i, &n_option);
	while (argv[i] != NULL)
	{
		printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_option == OFF)
		printf("\n");
	exit(EXIT_SUCCESS);
}

static void	echo_sub(char **argv, int *i, int *n_option)
{
	int	idx;
	int	tmp;

	idx = 1;
	while (argv[idx] != NULL)
	{
		if (ft_strncmp(argv[idx], "-n", 2) == SUCCESS)
		{
			tmp = 2;
			while (argv[idx][tmp] != '\0')
			{
				if (argv[idx][tmp] != 'n')
					break ;
				tmp++;
			}
			if (argv[idx][tmp] == '\0')
				(*n_option) = ON;
			else
				break ;
		}
		else
			break ;
		idx++;
	}
	(*i) = idx;
}
