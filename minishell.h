/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:07:10 by yaait-am          #+#    #+#             */
/*   Updated: 2025/03/22 15:35:22 by yaait-am         ###   ########.fr       */
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
# include <ctype.h>

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
	TYP_OAND
}		t_type;

typedef struct s_ast
{
	char			**cmd;
	t_type			type;
	int				exp;
	struct s_ast	*r;
	struct s_ast	*l;
}				t_ast;

extern t_ast	*g_ast;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_token
{
	char			*value;
	t_type			type;
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
t_ast 		*new_ast_node(t_type type, char *cmd, char *per, int exp);

#endif
