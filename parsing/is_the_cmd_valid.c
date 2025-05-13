/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_the_cmd_valid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:23:23 by yaait-am          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/12 12:47:58 by yaait-am         ###   ########.fr       */
=======
/*   Updated: 2025/04/27 15:14:19 by yaait-am         ###   ########.fr       */
>>>>>>> dahani
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
int	is_cmd_valid(t_token *tk, t_ast **node)
{
	t_token	*s;
	t_ast	*tmp;
=======
int	is_cmd_valid(t_token *tk)
{
	t_token	*s;
>>>>>>> dahani

	s = tk;
	if (!check_the_first(tk))
		return (0);
<<<<<<< HEAD
	tmp = build_the_tree(tk);
	if (!tmp)
		return (0);
	if (is_invalid_syntax(tmp))
		return (0);
	*node = tmp;
	return (1);
}

=======
	g_ast = build_the_tree(tk);
	if (!g_ast)
		return (0);
	return (1);
}

void	help_skiping(char **new, t_quote *q, char *s)
{
	while (s[q->i] && s[q->i] != '\'' && s[q->i] != '"')
		(*new)[q->j++] = s[q->i++];
}

>>>>>>> dahani
void	help_wildcard(t_token *tokens, t_token **new, t_token *s)
{
	if (tokens)
	{
		while (tokens)
		{
			add_token(new, tokens->value, tokens->type, 0);
			tokens = tokens->next;
		}
	}
	else
		add_token(new, s->value, s->type, 0);
}

void	expand_to_directories(char *s, t_token **new)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	i = 0;
	if (is_hide(s))
		i = 1;
	dir = opendir(".");
	if (dir == NULL)
		return ;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == DT_DIR)
		{
			if (entry->d_name[0] == '.' && i)
				add_token(new, entry->d_name, TYP_WORD, 0);
			else if (!i && entry->d_name[0] != '.')
				add_token(new, entry->d_name, TYP_WORD, 0);
		}
		entry = readdir(dir);
	}
	closedir(dir);
}

int	help_clcule(char **env, int *j, char *s, int *i)
{
<<<<<<< HEAD
	int		total;
	char	*env_value;
=======
	int	total;
>>>>>>> dahani

	total = 0;
	while (s[(*i)] && (ft_isalnum(s[(*i)])))
		(*env)[(*j)++] = s[(*i)++];
	(*env)[(*j)] = '\0';
	if ((*j) > 0)
<<<<<<< HEAD
	{
		env_value = my_getenv(*env, NULL);
		if (env_value)
			total += ft_strlen(env_value);
		else
			total += ft_strlen(*env) + 1;
	}
=======
		total += ft_strlen(getenv((*env)));
>>>>>>> dahani
	else
		total++;
	return (total);
}
