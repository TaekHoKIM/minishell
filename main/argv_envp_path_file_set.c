/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_envp_path_file_set.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:39:23 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/08 20:19:49 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	file_set(t_token_list *head, t_info *info)
{
	t_token_list	*tmp;

	tmp = head;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (tmp->type == IN_OPEN_D1 || tmp->type == IN_OPEN_D2)
			info->i_fd = open(tmp->token, O_RDONLY);
		else if (tmp->type == OUT_OPEN_D1)
			info->o_fd = open(tmp->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tmp->type == OUT_OPEN_D2)
			info->o_fd = open(tmp->token, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (info->i_fd == FAIL || info->o_fd == FAIL)
			return (ft_perror(tmp->token));
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static void argv_set(t_token_list *head, t_info *info)
{
    t_token_list    *tmp;
    int             i;

    tmp = head;
	info->cmd_cnt = 0;
    while (tmp != NULL && tmp->type != PIPE)
    {
        if (tmp->type == CMD || tmp->type == ARG)
            info->cmd_cnt++;
        tmp = tmp->next;
    }
    if (info->cmd_cnt == 0)
        return ;
    info->argv = ft_malloc(sizeof(char *), info->cmd_cnt + 1);
    info->argv[info->cmd_cnt] = NULL;
    i = 0;
    while (head != NULL && head->type != PIPE)
    {
        if (head->type == CMD || head->type == ARG)
        {
            info->argv[i] = ft_strdup(head->token);
            i++;
        }
        head = head->next;
    }
}

static void	envp_set(t_envp *envp, t_info *info)
{
	t_envp	*tmp;
	int		cnt;

	tmp = envp;
	cnt = 0;
	while (tmp != NULL)
	{
		cnt++;
		tmp = tmp->next;
	}
	if (cnt == 0)
		return ;
	info->envp = ft_malloc(sizeof(char *), cnt + 1);
	info->envp[cnt] = NULL;
	cnt = 0;
	while (envp != NULL)
	{
		info->envp[cnt] = ft_strdup(envp->line);
		cnt++;
		envp = envp->next;
	}
}

static void	path_set(t_envp *envp, t_info *info)
{
	ssize_t	i;

	i = 0;
	while (envp != NULL)
	{
		if (envp->line[0] == 'P' && envp->line[1] == 'A' &&
		envp->line[2] == 'T' && envp->line[3] == 'H' && envp->line[4] == '=')
		{
			info->path = ft_split(envp->line + 5, ':');
			break ;
		}
		i++;
		envp = envp->next;
	}
}

int	av_ev_path_file_set(t_token_list *head, t_envp *envp, t_info *info)
{
	if (file_set(head, info) == FAIL)
		return (FAIL);
	argv_set(head, info);
	envp_set(envp, info);
	path_set(envp, info);
	return (SUCCESS);
}
