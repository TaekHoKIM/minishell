/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_set_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:29:47 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/08 15:21:57 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	basic_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_parent_signal()
{
	signal(SIGINT, basic_sigint);
	signal(SIGQUIT, SIG_IGN);
}
