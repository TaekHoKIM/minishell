#include "../minishell.h"
#include <unistd.h>

int main()
{
	t_token_list	*head;
	char			*str;

	while (1)
	{
		str = readline("minishell :");
		head = NULL;
		tokenization(str, &head);
		display_list(&head);
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
	else if (type == IN_OPEN_D1)
		printf(" : TYPE[IN_OPEN_D1]\n");
	else if (type == IN_OPEN_D2)
		printf(" : TYPE[IN_OPEN_D2]\n");
	else if (type == OUT_OPEN_D1)
		printf(" : TYPE[OUT_OPEN_D1]\n");
	else if (type == OUT_OPEN_D2)
		printf(" : TYPE[OUT_OPEN_D2]\n");
	else if (type == WRONG_TYPE)
		printf(" : TYPE[WRONG_TYPE]\n");
	else if (type == END)
		printf(" : TYPE[END]\n");
}
