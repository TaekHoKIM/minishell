/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:11:28 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/21 17:59:20 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(void)
{
	char	dir[4096];

	if (getcwd(dir, sizeof(dir)) == NULL)
		exit(EXIT_FAILURE);
	printf("%s\n", dir);
	exit(EXIT_SUCCESS);
}
