/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:07:10 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/20 16:23:38 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <ctype.h>
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
# define INITIAL_SIZE 10
# define FT_ALLOC 1
# define FT_CLEAR 0

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
	TYP_OAND,
	TYP_PAR_BLOCK
}		t_type;

typedef struct s_ast
{
	char			**cmd;
	t_type			type;
	int				nor;
	int				exp;
	int				*suc;
	struct s_ast	*r;
	struct s_ast	*l;
}				t_ast;

extern t_ast	*g_ast;

typedef struct s_token
{
	char			*value;
	t_type			type;
	int				head;
	int				is_exp;
	struct s_token	*next;
}				t_token;

typedef struct s_cmd
{
	int				fd;
	char			*s;
	char			**cmd;
	int				flag;
	char			**all;
	int				*falgs;
	struct s_cmd	*r;
	struct s_cmd	*l;
}				t_cmd;

typedef struct s_spl
{
	int		i;
	int		token_count;
	char	*start;
	int		len;
	int		offset;
}				t_spl;

void		handler(int sig);
void		*ft_malloc(size_t size, short option);
t_list		*mem_alloc(size_t size);
size_t		ft_strlen(const char *c);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *src);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		split_the_cmd(t_cmd *data);
int			is_space(char c);
char		*ft_strndup(const char *s, size_t n);
int			handle_quote(t_cmd *data, int i);
int			handle_token(t_cmd *data, t_spl *spl);
int			is_special_char(char c);
int			ft_handle_token(t_cmd *data, t_spl *spl, int *i);
int			check_the_first(t_token *tk);
int			is_cmd_valid(t_token *tk);
int			is_root(char *cmd);
char		*ft_strcpy(char *dest, char const *src);
void		*ft_memset(void *s, int c, size_t n);
t_token		*tokenize(char **cmd);
int			nb_tok(char	*str);
int			check_the_exp(t_token *tk);
int			invalid_syntax(t_token *tk);
t_ast		*build_the_tree(t_token *tk);
t_ast		*new_ast_node(t_type type, char **cmd, int exp);
int			dup_the_token(t_cmd *data, t_spl *spl);
void		ft_node(t_ast **head, t_ast **cur_node, t_token *cur);
t_ast		*creat_nor_cmd(t_token *tk);
t_ast		*start_for_ast(t_token *tk);
t_ast		*ft_par_cmd(t_token *tk);
t_token		*creat_new(t_token *tk, t_token **op);
void		ft_new_node(t_token **head, t_token **cur_node, t_token *cur);
t_token		*find_the_head(t_token *tk);
void		add_token(t_token **head, char *value, t_type type);
t_token		*create_token(char *value, t_type type);
void		the_best_sep(t_token *tk, t_token **op);
int			lowest(t_token **tk, t_type h, t_token **op);
void		help_start(t_token *op, t_token *tk, t_ast **node);
int			parsing(t_cmd *data);
int			for_par(t_token **tk, t_token **op);
int			check_ast_is_valid(void);


void		print_error(char *message);

int			execute_ast(t_ast *node, char ***envp);





int		is_builtin(char **cmd);
int		ft_strcmp(const char *s1, const char *s2);
int		my_cd(char **cmd, char ***envp);
int		my_pwd(void);
int		my_echo(char **cmd);
int		my_env(char **cmd, char **envp);
int		my_export(char **cmd, char ***envp_ptr);
int		my_unset(char **cmd, char ***envp_ptr);
int		my_exit(char **cmd);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
char	**copy_env(char **env);
int 	handle_cd_chdir(char *target, char *oldpwd, char **cmd, char ***envp);
int		is_valid_identifier(char *name);
int		is_valid_env_assignment(char *arg);
char	*ft_strdup_custom(const char *s);
int		print_sorted_env(char **envp);
int		env_var_index(char *name, char **env);
int 	exec_external(t_ast *node, char **envp);
int		exec_pipe(t_ast *node, char ***env);
int		exec_builtin(t_ast *node, char ***envp_ptr);
int		exec_redirection(t_ast *node, char ***envp);
int		open_file(char *argv, int i);
int		typ_redin_fun(t_ast *node, char ***envp);
int		typ_redapp_fun(t_ast *node, char ***envp);

#endif
