#include "libft.h"

void	ft_lstrm(t_list **begin, t_list *prev, t_list *curr)
{
	if (curr == *begin)
		*begin = curr->next;
	else if (!curr->next)
		prev->next = NULL;
	else
		prev->next = curr->next;
	free(curr->content);
	free(curr);
}
