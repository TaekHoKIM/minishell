/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:20:44 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/21 17:59:00 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp != NULL)
	{
		if (tmp->key == ENV)
			printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
	exit(EXIT_SUCCESS);
}
