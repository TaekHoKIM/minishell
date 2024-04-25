#include "minishell.h"
#include <unistd.h>

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
		printf("TOKEN>>>%s|\n", now->token);
		now = now->next;
	}
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
