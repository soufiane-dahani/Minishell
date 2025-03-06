/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:46:43 by sodahani          #+#    #+#             */
/*   Updated: 2024/10/31 17:43:44 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}
/*int main ()
{
	t_list *head = NULL;
	t_list *new;

	new = ft_lstnew("Hello, World!");
	ft_lstadd_front(&head, new);
	new = ft_lstnew("This is a linked list.");
	 ft_lstadd_front(&head, new);
	  while (head) {
        printf("%s\n", (char *)head->content);
		head = head->next;
	  }
	   while (head) {
        t_list *temp = head;
        head = head->next;
        free(temp);
    }

}*/
