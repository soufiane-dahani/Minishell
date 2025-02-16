/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:24:58 by sodahani          #+#    #+#             */
/*   Updated: 2025/02/16 14:55:53 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void	usage(void);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	here_doc(char *limiter, int argc);
void	child_process(char *argv, char **envp);
void	execute(char *argv, char **envp);
char	*find_path(char *cmd, char **envp);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	error(void);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*removecharta(char *str, char *c);
char	*check_command_in_paths(char *cmd, char **paths);
char	*ft_strchr(const char *s, int c);
#endif