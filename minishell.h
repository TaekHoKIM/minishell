/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:48:25 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/14 16:45:18 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
#include <dirent.h>

# define CHILD_PID 0
# define SUCCESS 0
# define FAIL -1
# define ON 1
# define OFF 2
# define DQ 3
# define Q 4
# define YES_LIMITER 5
# define NO_LIMITER 6
# define OPEN_MAX 256
# define SIGINT_EXIT_CODE 1
# define NO_CHANGE -1
# define CMD_NOT_FOUND 127
# define STDIN 0
# define STDOUT 1
# define MAX_PATH 300
# define PARENT 2
# define CHILD 1

enum	e_type
{
	NONE,
	CMD,
	ARG,
	PIPE,
	IN_D1,
	IN_D2,
	OUT_D1,
	OUT_D2,
	IN_D1_ARG,
	IN_D2_ARG,
	OUT_D1_ARG,
	OUT_D2_ARG,
	IN_OPEN_D1,
	IN_OPEN_D2,
	OUT_OPEN_D1,
	OUT_OPEN_D2,
	WRONG_TYPE,
	// 개행 뒤에 온 모든 것을 하나의 토큰화 
	END
};

enum	e_builtin
{
	B_ECHO = 1,
	B_CD = 2,
	B_PWD = 3,
	B_EXPORT = 4,
	B_UNSET = 5,
	B_ENV = 6,
	B_EXIT = 7
};

typedef struct s_token_list{
	int					type;
	char				*token;
	struct s_token_list	*next;
}t_token_list;

typedef struct s_envp{
	char			*line;
	struct s_envp	*next;
}	t_envp;

typedef struct s_info
{
	char	**argv;
	int		builtin;
	int		cmd_cnt;
	char	**envp;
	int		exit_code;
	int		here_doc_cnt;
	int		i_fd;
	int		last_child_pid;
	int		o_fd;
	char	**path;
	pid_t	*pid;
	int		pipe_cnt;
	int		**pipefd;
}	t_info;

// ------------------------------------taekhkim-------------------------------------------
// main

// ft_str
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// ft_sub
char	*ft_lowercasing(char *cmd);

// make_token
int		make_token(char *str, int start, t_token_list **head);
int		make_token_sub(char *str, int start, t_token_list **head);
int		make_token_sub1(char *str, int start, int q, int flag);
int		str_to_token(char *str, int start, int i, t_token_list **head);
int		input_token(char *str, t_token_list **head);

// change_env
char	*change_env(char *str, t_envp *env, int exit_code);
int		change_env_flag(char c, int *flag);
char	*change_env_sub(char *str, int	*index, t_envp *env);
int		check_special_char(char *restr, int i);
int		change_env_sub1(char **restr, char *temp_str, int set[2], t_envp *env);


// change_env_sub
char	*remove_str(char *str, int start, int len);
char	*change_str(char *str, int start, char *change_str, int len);
void	change_str1(char *str, char *re_str, char *change_str, int set[2]);
char	*user_getenv(char *str, t_envp *env);

// delete_quotation
char	*delete_q(char *restr);
char	*delete_q_helper(char *restr, char q, int *s);
void	delete_q_helper1(char *str, char *restr, char q, int j);

// tokenization
int		tokenization(char *str, t_token_list **head, t_envp *env, int exit_code);
int		token_change(t_token_list **head, t_envp *env, int exit_code);
int		last_token_input(t_token_list **head);
int		token_check(t_token_list **head, t_envp *env, int exit_code);

// check_open_redi
int		check_open_redi(t_token_list **head);
void	check_open_redi_mid(t_token_list **in_temp, t_token_list **out_temp);
void	check_open_redi_last(t_token_list **in_temp, t_token_list **out_temp);

// token_type
int		input_type(t_token_list **head);
void	input_type_sub(t_token_list *now, int pre_type);
int		token_typing(t_token_list **head);
int		syntax_check_type(t_token_list **head);
int		check_cmd(t_token_list **head);

// remove_token
int		remove_token(t_token_list **head);
void	remove_token_sub(t_token_list *now);

// token_check
int		quotation_check(char *str);
int		is_space(char c);
void	list_free_k(t_token_list **head, char *error_msg);

// input_exit_code
char	*input_exit_code(char *str, int exit_code, int *i);
void	input_exit_code_sub(char *str, char *exit_str, char *re_str, int i);

// ------------------------------------taekhkim-------------------------------------------

// ------------------------------------minyekim-------------------------------------------


// kim_min_yeong

// argv_envp_path_set.c
int		av_ev_path_file_set(t_token_list *head, t_envp *envp, t_info *info);
void	argv_set(t_token_list *head, t_info *info);

// basic_set_signal.c
void	bagic_set_parent_signal();

// builtin_check_exec.c
void	builtin_check_exec(t_token_list *head, t_envp *envp, t_info *info);
int		ft_strcmp(char *s1, char *s2);

// child_fd_set.c
void	first_command_fd_set(t_info	*info, int i);
void	last_command_fd_set(t_info *info, int i);
void	middle_command_fd_set(t_info *info, int i);

// child_process.c
void	child_process(t_token_list *head, t_envp *envp, t_info *info, int i);
void	pipe_set(int i_fd, int o_fd);

// exec_process.c
void	exec_process(t_token_list *head, t_envp *envp, t_info *info);
void	close_fd(void);

// free.c
void	t_token_list_free(t_token_list **head);
void	array_2d_free(void **arr);

// ft_itoa.c
char	*ft_itoa(int n);

// ft_putstr_fd.c
void	ft_putstr_fd(char *s, int fd);

// ft_split.c
char	**ft_split(char const *s, char c);

// ft_strjoin.c
char	*ft_strjoin(char const *s1, char const *s2);

// get_next_line.c
char	*get_next_line(int fd);

// get_next_line_utils.c
int		find_enter(char *str);
char	*ensure_not_null(char *str);

// here_doc_set_signal.c
void	here_doc_parent_sigint(int sig);
void	here_doc_child_sigint(int sig);

// here_doc_utils.c
void	here_doc_file_unlink(int here_doc_cnt);
int		ft_limiter_check(char *str1, char *str2);

// here_doc.c
int		here_doc(char *filename, char *limiter);
void	fake_here_doc(char *limiter);
void	find_here_doc_and_process(t_token_list *head, t_info *info);
int		here_doc_preprocessor(t_token_list *head, t_info *info);

// minishell_utils.c
void	*ft_malloc(size_t size, size_t cnt);
int		ft_perror(char *str);
int		ft_chdir(char *path, t_info *info);
void	ctrl_d_print_exit();
void	info_terminal_signal_reset(t_info *info);

// minishell.c
int		main(int argc, char **argv, char **envp);

// set_envp.c
void	set_envp(t_envp **env, char **envp);

// set_terminal.c
void	set_terminal_not_print(void);
void	reset_terminal(void);

// wait.c
void	child_process_wait(t_info *info);

// ------------------------------------minyekim-------------------------------------------

// built_in/echo.c
void	echo(char **argv);
void	change_dir(t_token_list *head, t_envp *envp, t_info *info);
void	pwd(void);
void	env(t_envp *envp);
void	unset(t_envp **envp, char **argv);


#endif