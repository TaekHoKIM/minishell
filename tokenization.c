/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:32:47 by taekhkim          #+#    #+#             */
/*   Updated: 2024/04/24 18:18:21 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *change_env(char *str);

int	tokenization(char *str, t_token_list **head)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			i = make_token(str, i, head);
		if (i == FAIL)
		{
			printf("fail\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	make_token(char *str, int start, t_token_list **head)
{
	int		i;
	int		flag;
	char	*re_str;

	flag = OFF;
	if (str[start] == '\'' || str[start] == '\"')
		flag = ON;
	i = start + 1;
	while (1)
	{
		if ((str[i] == ' ' || str[i] == '\0') && flag == OFF)
			break ;
		if ((str[i] == '\"' || str[i] == '\'') && flag == ON)
			flag = OFF;
		else if ((str[i] == '\"' || str[i] == '\'') && flag == OFF)
			flag = ON;
		i++;
	}
	re_str = ft_substr(str, start, i - start);
	// printf("restr[%d] :%s\n",ft_strlen(re_str) ,re_str);
	// change_env(re_str);
	// re_str = delete_q(re_str); // 고쳐야함  "a"b'c' => abc
	if (re_str == NULL)
		exit(EXIT_FAILURE);
	input_token(re_str, head);
	return (i);
}

int	input_token(char *str, t_token_list **head)
{
	t_token_list	*new;
	t_token_list	*temp;

	new = (t_token_list *)malloc(sizeof(t_token_list) * 1);
	new->token = str;
	if ((*head) == NULL)
	{
		(*head) = new;
		new->next = NULL;
	}
	else
	{
		temp = (*head);
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->next = NULL;
	}
	return (SUCCESS);
}
// char *change_env(char *str)
// {
// 	int		i;
// 	int		j;
// 	int		flag;
// 	char	*temp_str;
// 	char	*env_str;

// 	i = 0;
// 	flag = ON;
// 	if (str[i] != '\0')
// 	{
// 		if (str[i] == '\'')
// 		{
// 			flag = OFF;
// 			i++;
// 		}
// 		if (str[i] == '$' && flag == ON)
// 		{
// 			j = 0;
// 			while (str[i + j] != ' ')
// 				j++;
// 			if (j != 1)
// 			{
// 				temp_str = ft_substr(str, i + 1, j - 1);
// 				env_str = getenv(temp_str);
// 				if (env_str == NULL)
// 					remove_str(str, i, j - 1);
// 			}
			
// 		}
// 	}

// 	return (temp_str);
// }

// char	*remove_str(char *str, int start, int len)
// {
// 	char	*re_str;
// 	int		i;

// 	re_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - len + 1));
// }