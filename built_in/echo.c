/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:20:36 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/15 02:28:41 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	i = 1;
	n_option = OFF;
	printf("built_in echo:");
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
	exit(EXIT_SUCCESS);
}
