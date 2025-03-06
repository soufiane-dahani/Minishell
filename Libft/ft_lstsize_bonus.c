/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:22:48 by sodahani          #+#    #+#             */
/*   Updated: 2024/10/31 18:13:48 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
/*int main ()
{
	t_list *head = NULL;
	t_list *new;

	new = ft_lstnew("Hello, World!");
	ft_lstadd_front(&head, new);
	new = ft_lstnew("This is a linked list.");
	 ft_lstadd_front(&head, new);
	  printf("res : %d", ft_lstsize(head));
	   while (head) {
        t_list *temp = head;
        head = head->next;
        free(temp);
    }

}*/
