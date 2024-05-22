NAME		=	minishell

SRCS		=	main/argv_envp_path_file_set.c		\
				main/basic_set_signal.c				\
				main/builtin_check_and_exec.c		\
				main/child_fd_set.c					\
				main/child_process.c				\
				main/exec_process.c					\
				main/free.c							\
				main/ft_atoi.c						\
				main/ft_itoa.c						\
				main/ft_putstr_fd.c					\
				main/ft_split.c						\
				main/ft_strjoin.c					\
				main/get_next_line_utils.c			\
				main/get_next_line.c				\
				main/here_doc_set_signal.c			\
				main/here_doc_utils.c				\
				main/here_doc.c						\
				main/minishell_utils.c				\
				main/minishell.c					\
				main/set_envp.c						\
				main/set_terminal.c					\
				main/wait.c							\
				tokenization/change_env_sub.c		\
				tokenization/change_env.c			\
				tokenization/delete_quotation.c		\
				tokenization/ft_str.c				\
				tokenization/make_token.c			\
				tokenization/token_check.c			\
				tokenization/token_type.c			\
				tokenization/tokenization.c			\
				tokenization/check_open_redi.c		\
				tokenization/input_exit_code.c		\
				tokenization/remove_token.c			\
				built_in/change_dir_utils.c			\
				built_in/change_dir.c				\
				built_in/echo.c						\
				built_in/env.c						\
				built_in/exit.c						\
				built_in/export_utils.c				\
				built_in/export.c					\
				built_in/pwd.c						\
				built_in/unset.c

OBJS	=	$(SRCS:.c=.o)

CC				=	cc
CCFLAGS			=	-Wall -Wextra -Werror
READLINE_LINK	=	-lreadline

all : $(NAME)

%.o : %.c
	$(CC) $(CCFLAGS) -I/opt/homebrew/opt/readline/include -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@ $(READLINE_LINK)

clean :
	rm -f $(OBJS)

fclean :
	rm -f ${NAME} $(OBJS)

re :
	make fclean
	make all

.PHONY : all clean fclean re