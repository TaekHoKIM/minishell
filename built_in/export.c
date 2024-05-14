/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:26:05 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/14 19:17:24 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	export_check_remove(t_envp *envp, char *arg);
static void	export_insert(t_envp **envp, char *arg);
static int	arg_check(char *arg);

int	export(t_envp *envp, char **argv)
{
	int	i;
	int	flag;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (argv[i] != NULL)
	{
		if (arg_check(argv[i]) == SUCCESS)
		{
			if (export_check_remove(envp, argv[i]) == SUCCESS)
				export_insert(&envp, argv[i]);
		}
		else
			exit_code = 1;
		i++;
	}
	return (exit_code);
}

static int	export_check_remove(t_envp *envp, char *arg)
{
	t_envp	*tmp;
	int		len;
	char	*env;

	len = 0;
	while (arg[len] != '=' && arg[len] != '\0')
		len++;
	if (len == ft_strlen(arg))
		return (FAIL);
	tmp = envp;
	while (tmp != NULL)
	{
		env = tmp->line;
		if (ft_strncmp(env, arg, len + 1) == SUCCESS)
		{
			free(tmp->line);
			tmp->line = NULL;
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}


static void	export_insert(t_envp **envp, char *arg)
{
	t_envp	*tmp;
	t_envp	*new;
	t_envp	*pre;
	char	*input_str;

	tmp = (*envp);
	pre = NULL;
	while (tmp != NULL)
	{
		if (tmp->line == NULL)
		{
			input_str = ft_strdup(arg);
			tmp->line = input_str;
			return ;
		}
		pre = tmp;
		tmp = tmp->next;
	}
	new = (t_envp *)ft_malloc(sizeof(t_envp), 1);
	input_str = ft_strdup(arg);
	new->line = input_str;
	new->next = NULL;
	if (pre != NULL)
		pre->next = new;
	else if ((*envp) == NULL)
		(*envp) = new;
	return ;
}

static int	arg_check(char *arg)
{
	int		len;
	int		i;
	char	c;

	len = 0;
	while (arg[len] != '\0' && arg[len] != '=')
		len++;
	c = arg[0];
	if (!(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_'))
		return (FAIL);
	i = 1;
	while (i < len)
	{
		c = arg[i];
		if (!(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')
				|| (c == '_') || ('0' <= c && c <= '9')))
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}
