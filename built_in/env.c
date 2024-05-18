/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:20:44 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/17 21:45:22 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	printf("built_in env\n");
	while (tmp != NULL)
	{
		if (tmp->key == ENV)
			printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
	exit(EXIT_SUCCESS);
}
