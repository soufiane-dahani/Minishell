/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:05:35 by sodahani          #+#    #+#             */
/*   Updated: 2024/11/01 16:31:21 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*void del_function(void *content) {
    printf("Deleting content: %s\n", (char *)content);
}
int main ()
{
	t_list *node = ft_lstnew("Node content");
	printf("Content before deletion: %s\n", (char *)node->content);
	ft_lstdelone(node, del_function);
}*/