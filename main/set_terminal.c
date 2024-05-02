/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:30:08 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/02 19:02:15 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_terminal_not_print(void)
{
	struct termios	term; // 터미널 설정이 담겨있는 termios 구조체

	if (tcgetattr(STDIN_FILENO, &term) == FAIL) // 현재 터미널의 설정을 term에 가져옴
		exit(EXIT_FAILURE);
	term.c_lflag &= ~(ECHOCTL); // 시그널표식 출력이 true 라면 false로 변경
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == FAIL) // 변경한 term 설정을 현재 터미널에 적용
		exit(EXIT_FAILURE);
}

void	reset_terminal(void)
{
	struct termios	term; // 터미널 설정이 담겨있는 termios 구조체

	if (tcgetattr(STDIN_FILENO, &term) == FAIL) // 현재 터미널의 설정을 term에 가져옴
		exit(EXIT_FAILURE);
	term.c_lflag |= (ECHOCTL); // 시그널표식 출력이 false 라면 true로 변경
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == FAIL)  // 변경한 term 설정을 현재 터미널에 적용
		exit(EXIT_FAILURE);
}