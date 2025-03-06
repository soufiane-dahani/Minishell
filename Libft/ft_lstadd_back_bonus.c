/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:46:34 by sodahani          #+#    #+#             */
/*   Updated: 2024/10/31 18:04:20 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	last = ft_lstlast(*alst);
	last->next = new;
}
/*int main ()
{
	t_list *head = NULL;
	t_list *new;

	new = ft_lstnew("dahani soufiane");
	ft_lstadd_back(&head, new);
	new = ft_lstnew("dahani mohamed");
	ft_lstadd_back(&head, new);
	while (head)
	{
		printf("%s\n", (char *)head->content);
		head = head->next;
	}
}*/
