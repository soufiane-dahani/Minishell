/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 09:30:25 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/25 14:46:55 by yaait-am         ###   ########.fr       */
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
# include <unistd.h>

typedef struct s_col
{
	char	**cmd;
}				t_col;

typedef struct s_cmd
{
	int				fd;
	char			*s;
	char			**cmd;
	char			**all;
	t_col			*col;
	struct t_cmd	*r;
	struct t_cmd	*l;
}				t_cmd;

int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			handler(int sig);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char *s1, char *s2);
int				ft_strlen(char *str);
int				check_is_valid(t_cmd *data);
int				is_built(t_cmd *data);
int				is_valid_args(t_cmd *data);


#endif
