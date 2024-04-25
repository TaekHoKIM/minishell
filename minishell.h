/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:48:25 by taekhkim          #+#    #+#             */
/*   Updated: 2024/04/26 00:40:57 by taekhkim         ###   ########.fr       */
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

enum	e_type
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

void	display_list(t_token_list **head);
void	list_free(t_token_list **head);


char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);

char	*change_env(char *str);
int		change_env_flag(char c, int *flag);
char	*change_env_sub(char *str, int	*index);
int		check_special_char(char *restr, int i);
int		change_env_sub1(char **restr, char *temp_str, int i, int j);

char	*remove_str(char *str, int start, int len);
char	*change_str(char *str, int start, char *change_str, int len);
void	change_str1(char *str, char *re_str, char *change_str, int start);

char	*delete_q(char *restr);
char	*delete_q_helper(char *restr, char q, int *s);
void	delete_q_helper1(char *str, char *restr, char q, int j);

int		tokenization(char *str, t_token_list **head);
int		make_token(char *str, int start, t_token_list **head);
int		input_token(char *str, t_token_list **head);
int		quotation_check(char *str);
int		str_to_token(char *str, int start, int i, t_token_list **head);




#endif