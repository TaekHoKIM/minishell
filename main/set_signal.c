/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:29:47 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/02 19:02:15 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ctrl_c(int sig)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
}

static void	ctrl_d(int sig)
{
	exit(EXIT_SUCCESS);
}

void	set_parent_signal()
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, ctrl_d);
}