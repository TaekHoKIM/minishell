/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:30:08 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/12 18:15:54 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_terminal_not_print(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == FAIL)
		exit(EXIT_FAILURE);
	term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == FAIL)
		exit(EXIT_FAILURE);
}

void	reset_terminal(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == FAIL)
		exit(EXIT_FAILURE);
	term.c_lflag |= (ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == FAIL)
		exit(EXIT_FAILURE);
}
