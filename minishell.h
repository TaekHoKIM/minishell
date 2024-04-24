/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:48:25 by taekhkim          #+#    #+#             */
/*   Updated: 2024/04/24 18:01:19 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define FAIL -1
# define ON 1
# define OFF 2
# define DQ 3
# define Q 4
enum e_type
{
	CMD,
	ARG,
	IN_D1,
	IN_D2,
	OUT_D1,
	OUT_D2
};
typedef struct s_token_list{
	int					type;
	char				*token;
	struct s_token_list	*next;
}t_token_list;

char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
int		make_token(char *str, int start, t_token_list **head);
int		input_token(char *str, t_token_list **head);
int		tokenization(char *str, t_token_list **head);
void	display_list(t_token_list **head);

char	*delete_q_helper(char *restr, char q);
char	*delete_q(char *restr);

#endif