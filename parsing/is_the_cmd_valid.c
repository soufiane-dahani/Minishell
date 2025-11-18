/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_the_cmd_valid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassir <yassir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:23:23 by yaait-am          #+#    #+#             */
/*   Updated: 2025/11/18 16:48:39 by yassir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_cmd_valid(t_token *tk, t_ast **node)
{
	t_ast	*tmp;

	if (!check_the_first(tk))
		return (0);
	tmp = build_the_tree(tk);
	if (!tmp)
		return (0);
	if (is_invalid_syntax(tmp))
		return (0);
	*node = tmp;
	return (1);
}

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
	int		total;
	char	*env_value;

	total = 0;
	while (s[(*i)] && (ft_isalnum(s[(*i)])))
		(*env)[(*j)++] = s[(*i)++];
	(*env)[(*j)] = '\0';
	if ((*j) > 0)
	{
		env_value = my_getenv(*env, NULL);
		if (env_value)
			total += ft_strlen(env_value);
		else
			total += ft_strlen(*env) + 1;
	}
	else
		total++;
	return (total);
}
