/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_set_signal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:01:08 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/15 00:07:22 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_print_newline(int sig)
{
	(void)sig;
	printf("\n");
}

void	here_doc_child_sigint(int sig)
{
	(void)sig;
	exit(SIGINT_EXIT_CODE);
}
