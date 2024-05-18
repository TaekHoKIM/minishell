/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:04:34 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/18 21:03:30 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_print(t_envp *envp)
{
	while (envp != NULL)
	{
		printf("declare -x ");
		if (envp->key == EXPORT)
			printf("%s\n", envp->line);
		else
			printf("\"%s\"\n", envp->line);
		envp = envp->next;
	}
}