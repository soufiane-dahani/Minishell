/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:20:10 by sodahani          #+#    #+#             */
/*   Updated: 2024/10/31 18:22:46 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
/*int main ()
{
	
	t_list *head = NULL;
	t_list *new;
	t_list *last;

	new = ft_lstnew("Hello, World!");
	ft_lstadd_front(&head, new);
	new = ft_lstnew("This is a linked list.");
	 ft_lstadd_front(&head, new);
	last = ft_lstlast(head);

	  while (last) {
        printf("%s\n", (char *)last->content);
		last = last->next;
	  }
	   while (head) {
        t_list *temp = head;
        head = head->next;
        free(temp);
    }
}*/
