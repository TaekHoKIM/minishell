#include "minishell.h"
#include <unistd.h>

void	type_print(t_token_list *now);

int main()
{
	t_token_list	*head;
	char			*str;

	while (1)
	{
		str = readline("minishell :");
		head = NULL;
		tokenization(str, &head); // 토큰화 된거 - 이거 아직 ""/'' 제거 처리를 안해줌
		display_list(&head); // 토큰화 된거 보여줌
	}
	return (0);
}

void	display_list(t_token_list **head)
{
	t_token_list	*now;

	now = (*head);
	while (now != NULL)
	{
		printf("TOKEN>>>[%s]", now->token);
		type_print(now);
		now = now->next;
	}
}

void	type_print(t_token_list *now)
{
	int	type;

	type = now->type;
	if (type == NONE)
		printf(" : TYPE[NONE]\n");
	else if (type == CMD)
		printf(" : TYPE[CMD]\n");
	else if (type == ARG)
		printf(" : TYPE[ARG]\n");
	else if (type == PIPE)
		printf(" : TYPE[PIPE]\n");
	else if (type == IN_D1)
		printf(" : TYPE[IN_D1]\n");
	else if (type == IN_D2)
		printf(" : TYPE[IN_D2]\n");
	else if (type == OUT_D1)
		printf(" : TYPE[OUT_D1]\n");
	else if (type == OUT_D2)
		printf(" : TYPE[OUT_D2]\n");
	else if (type == IN_D1_ARG)
		printf(" : TYPE[IN_D1_ARG]\n");
	else if (type == IN_D2_ARG)
		printf(" : TYPE[IN_D2_ARG]\n");
	else if (type == OUT_D1_ARG)
		printf(" : TYPE[OUT_D1_ARG]\n");
	else if (type == OUT_D2_ARG)
		printf(" : TYPE[OUT_D2_ARG]\n");
	else if (type == IN_OPEN)
		printf(" : TYPE[IN_OPEN]\n");
	else if (type == OUT_OPEN)
		printf(" : TYPE[OUT_OPEN]\n");
	else if (type == WRONG_TYPE)
		printf(" : TYPE[WRONG_TYPE]\n");
}

void	list_free(t_token_list **head)
{
	t_token_list	*temp;
	t_token_list	*remove;

	temp = *head;
	if (temp == NULL)
		return ;
	while (temp->next != NULL)
	{
		remove = temp;
		temp = temp->next;
		free(remove);
	}
	return ;
}
