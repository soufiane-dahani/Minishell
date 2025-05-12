/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_the_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:21:32 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/12 13:22:58 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_getenv(char *s, char **copy)
{
	int			i;
	int			len;
	static char	**env;

	if (copy)
		env = copy;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], s, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	more_help_for_add_match(int count, char **new, int *matches, char *s)
{
	int	found;

	found = 0;
	if (count == 0)
		new[(*matches)++] = ft_strdup(s);
	else
		found = 1;
	return (found);
}

void	add_matches(char **new, char *s, int *mat, int *found_match)
{
	DIR				*dir;
	struct dirent	*entry;
	int				is_hide;
	int				is_dir;
	int				count;

	(1) && (count = 0), (is_hide = (s[0] == '.'));
	is_dir = (ft_strchr(s, '/') != NULL);
	dir = opendir(".");
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		if ((!is_hide && entry->d_name[0] == '.')
			|| (is_dir && entry->d_type != DT_DIR))
		{
			entry = readdir(dir);
			continue ;
		}
		count += help_add_match(entry, new, s, mat);
		entry = readdir(dir);
	}
	closedir(dir);
	*found_match = more_help_for_add_match(count, new, mat, s);
}

int	is_invalid_syntax(t_ast *node)
{
	if (!node)
		return (0);
	if ((node->type == TYP_PIPE || node->type == TYP_AND ||
		node->type == TYP_OR) && !node->r)
	{
		printf("invalid syntax near `%s'\n", node->cmd[0]);
		return (1);
	}
	if (is_invalid_syntax(node->l))
		return (1);
	if (is_invalid_syntax(node->r))
		return (1);
	return (0);
}
