/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:57:29 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/11 03:57:36 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_envp(t_envp **env, char **envp)
{
	t_envp	*new;
	t_envp	*tmp;
	int		i;

	i = 0;
	while(envp[i] != NULL)
	{
		new = ft_malloc(sizeof(tmp), 1);
		new->line = ft_strdup(envp[i]);
		new->next = NULL;
		if (i == 0)
			*env = new;
		else
		{
			tmp = *env;
			while ((tmp)->next != NULL)
				tmp = tmp->next;
			tmp->next = new;
		}
		i++;
	}
}

void	*ft_malloc(size_t size, size_t cnt)
{
	void	*tmp;

	tmp = malloc(sizeof(size) * cnt);
	if (tmp == NULL)
		exit(EXIT_FAILURE);
	return (tmp);
}

int	ft_perror(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(str);
	return (FAIL);
}

void	ft_chdir(char *path)
{
	if (chdir(path) == FAIL)
	{
		ft_perror("chdir");
		exit(EXIT_FAILURE);
	}
}

static void	old_pwd_set(t_envp *envp, char *pwd)
{
	while (envp != NULL)
	{
		if (envp->line[0] == 'O' && envp->line[1] == 'L'
			&& envp->line[2] == 'D' && envp->line[3] == 'P'
			&& envp->line[4] == 'W' && envp->line[5] == 'D'
			&& envp->line[6] == '=')
		{
			free(envp->line);
			envp->line = ft_strjoin("OLDPWD=", pwd);
			break ;
		}
		envp = envp->next;
	}
}

static void	pwd_set(t_envp *envp)
{
	char	buf[MAX_PATH];
	char	*path;

	path = getcwd(buf, MAX_PATH);
	if (path == NULL)
	{
		ft_perror("getcwd");
		exit(EXIT_FAILURE);
	}
	while (envp != NULL)
	{
		if (envp->line[0] == 'P' && envp->line[1] == 'W'
			&& envp->line[2] == 'D' && envp->line[3] == '=')
		{
			free(envp->line);
			envp->line = ft_strjoin("PWD=", path);
			break ;
		}
		envp = envp->next;
	}
	// free(path);
}

void	test_change_dir(t_envp *envp, char *argv)
{
	char	buf[MAX_PATH];
	char	*path;

	path = getcwd(buf, MAX_PATH);
	if (path == NULL)
	{
		ft_perror("getcwd");
		exit(EXIT_FAILURE);
	}
	if (argv == NULL)
		ft_chdir("/Users/minyekim");
	else
		ft_chdir(argv);
	old_pwd_set(envp, path);
	pwd_set(envp);
	// free(path);
	// exit(EXIT_SUCCESS);
}

// void	leak()
// {
// 	system("leaks a.out");
// }

int	main(int argc, char **argv, char **envp)
{
	// atexit(leak);
	t_envp *env;
	char	buf[MAX_PATH];
	char	*path1;
	char	*path2;

	set_envp(&env, envp);
	path1 = getcwd(buf, MAX_PATH);
	printf("%s\n", path1);
	test_change_dir(env, NULL);
	system("pwd");
}