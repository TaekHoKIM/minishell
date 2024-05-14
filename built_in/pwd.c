/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:11:28 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/15 02:29:58 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(void)
{
	char	dir[4096];

	if (getcwd(dir, sizeof(dir)) == NULL)
		exit(EXIT_FAILURE);
	printf("built_in pwd:");
	printf("%s\n", dir);
	exit(EXIT_SUCCESS);
}
