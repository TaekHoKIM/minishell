/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:20:44 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/15 02:29:16 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(t_envp *envp)
{
	t_envp	*temp;

	temp = envp;
	printf("built_in env\n");
	while (temp != NULL)
	{
		printf("%s\n", temp->line);
		temp = temp->next;
	}
	exit(EXIT_SUCCESS);
}
