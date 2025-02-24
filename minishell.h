/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 09:30:25 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/24 14:45:44 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_cmd
{
	int				fd;
	char			*s;
	char			**cmd;
	char			**all;
	struct t_cmd	*r;
	struct t_cmd	*l;
}				t_cmd;

int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		handler(int sig);
char		**ft_split(char const *s, char c);

#endif
