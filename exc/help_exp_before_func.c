/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_exp_before_func.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:26:07 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/05 10:03:29 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	for_quote(t_quote *q, char *str, char **new)
{
	if (str[q->j] == '"' || str[q->j] == '\'')
	{
		q->ch = str[q->j];
		(*new)[q->i++] = str[q->j++];
		while (str[q->j] && str[q->j] != q->ch)
			(*new)[q->i++] = str[q->j++];
		if (str[q->j] == q->ch)
			(*new)[q->i++] = str[q->j++];
	}
}

void	help_quoute(char *str, char **new, t_quote *q)
{
	if (str[q->j] == '\'')
	{
		(*new)[q->i++] = str[q->j++];
		while (str[q->j] && str[q->j] != '\'')
			(*new)[q->i++] = str[q->j++];
		if (str[q->j] == '\'')
			(*new)[q->i++] = str[q->j++];
	}
	if (str[q->j] == '$' && str[q->j + 1] != '"')
		store_new(new, &q->j, str, &q->i);
	else
	{
		if (str[q->j] != '$')
			(*new)[q->i++] = str[q->j++];
		else
			q->j++;
	}
}

char	*before_quote(char *str)
{
	t_quote	q;
	char	*env;
	char	*new;

	env = ft_malloc(ft_strlen(str) * sizeof(char) + 1, FT_ALLOC);
	q.a = calculate_s(str, env);
	q.j = 0;
	q.i = 0;
	new = ft_malloc(((sizeof(char)) * q.a) + 1, FT_ALLOC);
	while (str[q.j])
	{
		if (str[q.j] && (str[q.j] == '"' || str[q.j] == '\''))
			for_quote(&q, str, &new);
		else
			help_quoute(str, &new, &q);
	}
	new[q.i] = '\0';
	return (new);
}

char **handle_wildcards_for_string(char **s)
{
    DIR *dir;
    struct dirent *entry;
    char **new;
    int i = 0;
    int entry_count = 0;
    dir = opendir(".");
    if (!dir)
        return s;
    entry = readdir(dir);
    while (entry)
    {
        entry_count++;
        entry = readdir(dir);
    }
    closedir(dir);
    new = ft_malloc(sizeof(char *) * (entry_count + 1), FT_ALLOC);
    if (!new)
        return s;
    i = 0;
    int matches = 0;
    while (s[i])
    {
        int has_wildcard = 0;
        int j = 0;
        while (s[i][j])
        {
            if (s[i][j] == '*')
            {
                has_wildcard = 1;
                break;
            }
            j++;
        }
        if (has_wildcard)
        {
            dir = opendir(".");
            if (!dir)
            {
                i++;
                continue;
			}
            entry = readdir(dir);
            while (entry)
            {
                if (match_pattern(s[i], entry->d_name))
                    new[matches++] = ft_strdup(entry->d_name);
                entry = readdir(dir);
            }
            closedir(dir);
        }
        else
            new[matches++] = ft_strdup(s[i]);
        i++;
    }
    new[matches] = NULL;
    return new;
}
