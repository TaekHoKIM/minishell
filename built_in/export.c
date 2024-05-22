/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:26:05 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/22 18:08:07 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	export_insert(t_envp **envp, char *arg, int key)
{
	t_envp	*tmp;
	t_envp	*new;
	t_envp	*prev;

	tmp = (*envp);
	prev = NULL;
	while (tmp != NULL)
	{
		if (tmp->line == NULL)
		{
			tmp->line = ft_strdup(arg);
			tmp->key = key;
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	new = (t_envp *)ft_malloc(sizeof(t_envp), 1);
	new->line = ft_strdup(arg);
	new->key = key;
	new->next = NULL;
	if (*envp == NULL)
		*envp = new;
	else
		prev->next = new;
}

static int	add_export_list(t_envp *envp, char *arg)
{
	t_envp	*tmp;
	int		i;

	tmp = envp;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->line[i] != '\0' && arg[i] != '\0' && tmp->line[i] == arg[i])
		{
			if ((tmp->line[i + 1] == '=' && arg[i + 1] == '\0')
				|| (tmp->line[i + 1] == '\0' && arg[i + 1] == '\0'))
				return (FAIL);
			i++;
		}
		tmp = tmp->next;
	}
	export_insert(&envp, arg, EXPORT);
	return (EXPORT);
}

static int	export_check_remove(t_envp *envp, char *arg)
{
	t_envp	*tmp;
	int		len;
	char	*env;

	len = 0;
	while (arg[len] != '=' && arg[len] != '\0')
		len++;
	if (arg[len] == '\0')
		return (add_export_list(envp, arg));
	tmp = envp;
	while (tmp != NULL)
	{
		env = tmp->line;
		if (ft_strncmp(env, arg, len) == SUCCESS
			&& arg[len] == '=' && ft_strcmp(env, arg) == FAIL)
		{
			free(tmp->line);
			tmp->line = NULL;
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static int	arg_check(char *argv)
{
	int		idx;

	idx = 0;
	if ('0' <= argv[0] && argv[0] <= '9')
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(argv, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (FAIL);
	}
	while (argv[idx] != '\0' && (idx == 0 || argv[idx] != '='))
	{
		if (!(('A' <= argv[idx] && argv[idx] <= 'Z')
				|| ('a' <= argv[idx] && argv[idx] <= 'z')
				|| ('0' <= argv[idx] && argv[idx] <= '9')
				|| ('_' == argv[idx])))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(argv, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (FAIL);
		}
		idx++;
	}
	return (SUCCESS);
}

int	export(t_token_list *head, t_envp *envp, t_info *info)
{
	int	i;

	if (info->pipe_cnt != 0)
		return (FAIL);
	i = 1;
	argv_set(head, info);
	while (info->argv[i] != NULL)
	{
		if (arg_check(info->argv[i]) == SUCCESS)
		{
			if (export_check_remove(envp, info->argv[i]) == SUCCESS)
				export_insert(&envp, info->argv[i], ENV);
		}
		else
			info->exit_code = 1;
		i++;
	}
	if (i == 1)
		export_print(envp);
	return (SUCCESS);
}

// export test=123 이후 export test하면 변경 없음 - export 단독 사용시 나오는 것 처리
// unset 이후에 env 실행 되는 문제, 명령어 없는 문구 안뜨는 문제