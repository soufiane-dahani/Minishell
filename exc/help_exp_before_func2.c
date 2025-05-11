/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_exp_before_func2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:26:07 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/11 15:25:17 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_string(char **new, char *str, int *matches)
{
	if (has_wildcard_char(str))
		add_matches(new, str, matches);
	else
		new[(*matches)++] = ft_strdup(str);
}

int	calcule_total_len(char **cmd, int i)
{
	int		j;
	char	**split;
	int		a;

	j = 0;
	a = 0;
	while (cmd[j] && j < i)
		j++;
	if (cmd[j])
	{
		split = ft_split(cmd[j], ' ');
		while (split[a])
			a++;
		j++;
	}
	while (cmd[j])
		j++;
	return (a + j);
}

char	**split_the_no_quoted(char **cmd, int *i)
{
	int		j;
	int		size;
	char	**new;
	char	**spl;
	int		a;

	j = 0;
	a = 0;
	if (!cmd || !cmd[0] || !cmd[0][0])
		return (cmd);
	size = calcule_total_len(cmd, *i);
	new = ft_malloc((size + 1) * sizeof(char *), FT_ALLOC);
	while (cmd[j] && j < *i)
		new[a++] = ft_strdup(cmd[j++]);
	size = 0;
	if (cmd[j])
	{
		spl = ft_split(cmd[j], ' ');
		while (spl[size])
			new[a++] = ft_strdup(spl[size++]);
		j++;
	}
	while (cmd[j])
		new[a++] = ft_strdup(cmd[j++]);
	return (new[a] = NULL, new);
}

void	exit_for_child(void)
{
	perror("execve");
	ft_malloc(0, FT_CLEAR);
	exit(1);
}

void	init_var_for_wlidcards(t_init *wild, char **s)
{
	wild->s_count = 0;
	while (s[wild->s_count])
		wild->s_count++;
	wild->entries = count_entries();
	if (wild->entries < wild->s_count)
		wild->entries = wild->s_count;
	wild->new = ft_malloc(sizeof(char *) * (wild->entries + 1), FT_ALLOC);
}
