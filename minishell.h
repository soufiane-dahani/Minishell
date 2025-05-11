/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:07:10 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/11 19:13:10 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>

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
}					t_type;

typedef struct s_token
{
	char			*value;
	t_type			type;
	int				head;
	int				is_exp;
	struct s_token	*next;
}					t_token;

typedef struct s_ast
{
	char			**cmd;
	t_type			type;
	int				nor;
	int				exp;
	int				exit_status;
	char			**env;
	int				sign;
	int				shell;
	struct s_ast	*r;
	struct s_ast	*l;
	t_token			*redir;
}					t_ast;

typedef struct s_export_store
{
	char			**vars;
}					t_export_store;

extern int			g_exit;

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
}					t_cmd;

typedef struct s_spl
{
	int				i;
	int				token_count;
	char			*start;
	int				len;
	int				offset;
}					t_spl;

typedef struct s_q
{
	int				a;
	int				i;
	int				j;
	char			ch;
}					t_quote;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_init
{
	char	**new;
	int		i;
	int		j;
	int		matches;
	int		has_wildcard;
	int		s_count;
	int		entries;
}			t_init;

void				help_the_spleter(int size, char **new);
char				**fix_the_issuse_with_echo(char **cmd);
void				init_var_for_wlidcards(t_init *wild, char **s);
int					is_has_quote(char *s);
int					is_single(char *s);
int					is_couple(char *s);
char				*before_quote(char *c);
void				*ft_malloc(size_t size, short option);
t_list				*mem_alloc(size_t size);
size_t				ft_strlen(const char *c);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_split2(char *str, char *charset);
char				*ft_strdup(const char *src);
char				*ft_strchr(const char *s, int c);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				split_the_cmd(t_cmd *data);
int					is_space(char c);
char				*ft_strndup(const char *s, size_t n);
int					handle_quote(t_cmd *data, int i);
int					handle_token(t_cmd *data, t_spl *spl);
int					is_special_char(char c);
int					ft_handle_token(t_cmd *data, t_spl *spl, int *i);
int					check_the_first(t_token *tk);
int					is_cmd_valid(t_token *tk, t_ast **node);
char				*ft_strcpy(char *dest, char const *src);
void				*ft_memset(void *s, int c, size_t n);
t_token				*tokenize(char **cmd);
int					nb_tok(char *str);
int					check_the_exp(t_token **tk);
int					invalid_syntax(t_token *tk);
t_ast				*build_the_tree(t_token *tk);
int					dup_the_token(t_cmd *data, t_spl *spl);
int					is_token_sep(t_type s);
t_ast				*start_for_ast(t_token *tk);
t_token				*change_the_cards(char *pattern);
t_token				*creat_new(t_token *tk, t_token **op);
void				ft_new_node(t_token **head, t_token **cur_node,
						t_token *cur);
t_token				*find_the_head(t_token *tk);
void				add_token(t_token **head, char *value, t_type typ, int exp);
t_token				*create_token(char *value, t_type type, int exp);
void				the_best_sep(t_token *tk, t_token **op);
int					lowest(t_token **tk, t_type h, t_token **op);
void				help_start(t_token *op, t_token **tk, t_ast **node);
int					parsing(t_cmd *data, t_ast **node);
t_token				*fix_the_case(t_token *tk);
t_token				*fixing(t_token *tk);
t_token				*handle_wildcard(t_token *tk);
t_token				*handle_exp_quote(t_token *tk);
char				*skip_quote(char *s);
char				*new_with_exp(char *s);
int					calculate_s(char *s, char *env);
void				store_new(char **new, int *i, char *s, int *old);
void				help_skiping(char **new, t_quote *q, char *s);
void				setup_interactive_signals(void);
void				reset_signals(void);
void				handler_interactive(int sig);
char				*extra_work(char *s);
int					is_token(char c);
char				*ft_itoa(int n);
int					ft_isalnum(int c);
int					is_exit(char **new, int *i, char *s, int *old);
int					is_question(char *s, int *i);
void				help_wildcard(t_token *tokens, t_token **new, t_token *s);
void				expand_to_directories(char *s, t_token **new);
int					is_hide(char *s);
int					help_clcule(char **env, int *j, char *s, int *i);
int					is_token_nor(t_type s);
char				*for_herdoc(char *s);
char				*my_getenv(char *s, char **copy);
t_token				*handele_herdoc(t_token *tk);
char				*exp_for_herdoc(char *s);
void				creat_the_cmd(t_ast **node, t_token **tk);
char				*random_str(void);
char				**handle_exp_for_camond(char **cmd);
char				**handle_wildcards_for_string(char **s);
int					match_pattern(const char *pattern, const char *str);
void				handle_signal_for_herdoc(int sig);
int					calcul_herdoc(t_token *tk);
int					execute_ast(t_ast *node, char ***envp,
						t_export_store *store);
int					is_builtin(char **cmd);
int					ft_strcmp(const char *s1, const char *s2);
int					my_cd(char **cmd, char ***envp);
int					my_pwd(char **env);
int					my_echo(char **cmd);
int					my_env(char **cmd, char **envp);
int					my_export(char **args, char ***envp_ptr,
						t_export_store *store);
int					my_unset(char **cmd, char ***envp_ptr);
int					my_exit(char **cmd);
char				*ft_strjoin3(char *s1, char *s2, char *s3);
char				**copy_env(char **env);
int					handle_cd_chdir(char *target, char *oldpwd, char **cmd,
						char ***envp);
int					is_valid_identifier(char *name);
int					is_valid_env_assignment(char *arg);
char				*ft_strdup_custom(const char *s);
int					print_sorted_env(char **envp, t_export_store *store);
int					env_var_index(char *name, char **env);
int					exec_external(t_ast *node, char **envp);
int					exec_pipe(t_ast *node, char ***envp, t_export_store *store);
int					exec_builtin(t_ast *node, char ***envp_ptr,
						t_export_store *store);
int					open_file(char *argv, int i);
int					exec_and(t_ast *node, char ***envp, t_export_store *store);
int					exec_or(t_ast *node, char ***envp, t_export_store *store);
int					exec_subshell(t_ast *node, char ***envp,
						t_export_store *store);
char				*get_env_value(char **envp, const char *name);
int					find_env_index(char **envp, const char *name);
char				*expand_tilde(char *path, char **envp);
int					update_existing_env(char *key, char *value, char ***envp);
int					count_env_entries(char ***envp);
int					create_and_copy_env(char ***envp, char ***new_env,
						int count);
int					ft_strchr2(char *cmd, char c);
int					my_echo(char **cmd);
char				**add_new_env_if_not_found(void);
void				add_shlvl(char ***env);
void				store_export_only_var(const char *key,
						t_export_store *store);
void				remove_export_only_var(char **env, t_export_store *store);
t_token				*skip_par(t_token *tk);
void				update_env_plus(char *var, char ***envp_ptr);
char				*ft_strdup_custom2(const char *s);
char				*remove_plus(char *arg);
void				append_env_var(char *new_var, char ***envp_ptr);
void				add_or_update_env(char *arg, char ***envp_ptr);
int					ft_env_size(char **envp);
void				sort_env(char **env);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
char				*ft_itoa(int n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *str, int fd);
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *s, int c);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int					ft_isalnum(int c);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
int					exit_status(int status);
char				*check_command_in_paths(char *cmd, char **paths);
int					apply_redirections(t_ast *node, char ***envp,
						t_export_store *store);
char				*random_str(void);
int					count_entries(void);
void				child_process2(t_ast *node, char **envp);
void				execute(char **cmd, char **envp);
void				execute_with_path(char **cmd, char **envp);
int					has_wildcard_char(char *str);
void				process_string(char **new, char *str, int *matches);
int					is_valid_enclosure(t_token *start, t_token *end);
t_token				*create_inner_tokens(t_token *start, t_token *end);
char				*process_heredoc_content(char *content, char *name,
						t_token *tmp);
void				create_heredoc_tokens(t_token **new, char *name);
int					process_token(t_token **new, t_token **tmp, int a);
void				*setup_signals(void);
void				restore_signals(void);
void				change_herdoc_to_red(t_token **new, t_token **tmp, int a);
void				add_matches(char **new, char *pattern, int *matches);
char				**split_the_no_quoted(char **cmd, int *i);
void				print_env_line(char *var);
void				exit_for_child(void);

#endif
