#include "minishell.h"
#include <unistd.h>

int main()
{
	t_token_list	*head;
	char			*str;

	str = readline("minishell :");
	head = NULL;
	tokenization(str, &head);
	display_list(&head);
	return (0);
}

void	display_list(t_token_list **head)
{
	t_token_list	*now;

	now = (*head);
	while (now != NULL)
	{
		printf("%s$\n",now->token);
		now = now->next;
	}
}
