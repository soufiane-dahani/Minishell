/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:04:53 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/17 11:42:06 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <dirent.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

# define ANSI_COLOR_RED "\x1b[33m"
# define ANSI_RESET_ALL "\x1b[0m"

typedef enum e_type
{
	TYP_WORD,
	TYP_PIPE,
	TYP_DQUOTE,
	TYP_SQOUTE,
	TYP_REDIN,
	TYP_REDOUT,
	TYP_REDHERE,
	TYP_REDAPP,
	TYP_LPAR,
	TYP_RPAR,
	TYP_AND,
	TYP_OR,
	TYP_OAND
}		t_type;
#define PIPE TYP_PIPE

typedef struct s_ast
{
	char			**cmd;
	t_type			type;
	int				nor;
	int				exp;
	int				suc;
	struct s_ast	*r;
	struct s_ast	*l;
	struct s_ast	*next;
}				t_ast;

extern t_ast	*g_ast;

void		print_error(char *message);
int			execute_cd(char *path);
int execute_pwd(void);
int execute_exit(void);
int execute_unset(char ***envp, char *var_name);
int	execute_simple_command(char **cmd, char **envp);
char		*find_path(char *cmd, char **envp);
char		*check_command_in_paths(char *cmd, char **paths);
int execute_export(char ***envp, char **cmd);
int execute_env(char **envp);
void		error(void);
int	execute_pipe(t_ast *node, char **envp);
void		execute_ast(t_ast *node, char ***envp_ptr, int *exit_status);
int print_export(char **envp);
int is_valid_identifier(const char *var);
int add_to_env(char ***envp, const char *new_var);


void	free_split(char **arr);


#endif