/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:26:05 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/16 16:48:13 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	export_insert(t_envp **envp, char *arg)
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
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	new = (t_envp *)ft_malloc(sizeof(t_envp), 1);
	new->line = ft_strdup(arg);
	new->next = NULL;
	if (*envp == NULL)
		*envp = new;
	else
		prev->next = new;
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

static int	arg_check(char *argv)
{
	int		len;
	int		idx;
	char	c;

	len = 0;
	while (argv[len] != '\0' && argv[len] != '=')
		len++;
	idx = 0;
	while (idx < len)
	{
		if (!((idx == 0 && '_' == argv[idx])
				|| ('A' <= argv[idx] && argv[idx] <= 'Z')
				|| ('a' <= argv[idx] && argv[idx] <= 'z')
				|| ('0' <= argv[idx] && argv[idx] <= '9')))
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
	int	flag;

	if (info->pipe_cnt != 0)
		return (FAIL);
	i = 0;
	argv_set(head, info);
	while (info->argv[i] != NULL)
	{
		if (arg_check(info->argv[i]) == SUCCESS)
		{
			if (export_check_remove(envp, info->argv[i]) == SUCCESS)
				export_insert(&envp, info->argv[i]);
		}
		else
			info->exit_code = 1;
		i++;
	}
	return (SUCCESS);
}


// export test=123 이후 export test하면 변경 없음 - export 단독 사용시 나오는 것 처리
// exit 문구 위치 - 현재 실행 하는 라인의 마지막에 붙여야함 - 현재 고정으로 되어 있는 것 같음
// unset 이후에 env 실행 되는 문제, 명령어 없는 문구 안뜨는 문제