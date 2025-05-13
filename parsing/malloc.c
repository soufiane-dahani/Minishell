/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:33:12 by yaait-am          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/11 19:12:55 by yaait-am         ###   ########.fr       */
=======
/*   Updated: 2025/04/27 12:09:52 by yaait-am         ###   ########.fr       */
>>>>>>> dahani
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*mem_alloc(size_t size)
{
	t_list	*new;
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_malloc(0, FT_CLEAR);
		free(ptr);
		exit(EXIT_FAILURE);
	}
	new = ft_lstnew(ptr);
	if (!new)
	{
		ft_malloc(0, FT_CLEAR);
		free(ptr);
		exit(EXIT_FAILURE);
	}
	return (new);
}

void	*ft_malloc(size_t size, short option)
{
	static t_list	*head;
	t_list			*new;

	if (option == FT_ALLOC)
	{
		new = mem_alloc(size);
		if (!new)
			return (NULL);
		ft_lstadd_back(&head, new);
		return (new->content);
	}
	if (option == FT_CLEAR)
		ft_lstclear(&head, free);
	return (NULL);
}

int	is_question(char *s, int *i)
{
	char	*num;
	int		len;

	if (s[*i] == '?')
	{
<<<<<<< HEAD
		num = ft_itoa(g_exit);
=======
		num = ft_itoa(g_ast->exit_status);
>>>>>>> dahani
		len = ft_strlen(num);
		(*i)++;
		return (len);
	}
	else
		return (1);
}
<<<<<<< HEAD

void	help_the_spleter(int size, char **new)
{
	int	k;

	k = 0;
	while (k <= size)
		new[k++] = NULL;
}
=======
>>>>>>> dahani
