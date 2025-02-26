#include "libft/libft.h"
#include <stdio.h>

#define FT_ALLOC 1
#define FT_CLEAR 0

typedef t_list gc;
void	*ft_malloc(size_t size, short option);

gc		*mem_alloc(size_t size)
{
	gc	*new;
	void	*ptr;

	ptr = malloc(size);
	new = ft_lstnew(ptr);
	if (!ptr || !new)
	{
		ft_malloc(0, FT_CLEAR);
		exit(EXIT_FAILURE);
	}
	return (new);
}

void	*ft_malloc(size_t size, short option) {
	static gc 	*head;
	gc 			*new;
	if (option == FT_ALLOC) {
		new = mem_alloc(size);
		ft_lstadd_back(&head, new);
		return (new->content);
	}
	if (option == FT_CLEAR)
		ft_lstclear(&head, free);
	return (NULL);
}

int main(void) {

	char *string  = ft_malloc(sizeof(char *), FT_ALLOC);
	string = ft_malloc(sizeof(char *), FT_ALLOC);
	string = ft_malloc(sizeof(char *), FT_ALLOC);
	string = ft_malloc(sizeof(char *), FT_ALLOC);
	string = ft_malloc(sizeof(char *), FT_ALLOC);

	ft_malloc(0, FT_CLEAR);
}
