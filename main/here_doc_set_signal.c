/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_set_signal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:01:08 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/08 15:20:28 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	here_doc_parent_sigint(int sig)
{
	(void)sig;
	printf("\n");
}

void	here_doc_child_sigint(int sig)
{
	(void)sig;
	exit(SIGINT_EXIT_CODE);
}