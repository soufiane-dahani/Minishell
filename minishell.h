/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:04:53 by sodahani          #+#    #+#             */
/*   Updated: 2025/02/25 13:39:26 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <termcap.h>
# include "Libft/libft.h"

#define ANSI_COLOR_RED          "\x1b[33m"
#define ANSI_RESET_ALL          "\x1b[0m"



typedef enum {
    SIMPLE_CMD,
    PIPE,         
    REDIRECT_IN,
    REDIRECT_OUT,
    APPEND_OUT,  
    AND,          
    OR            
} t_ast_node_type;

typedef struct s_ast_node {
    t_ast_node_type type;           // The type of the node (e.g., SIMPLE_CMD, PIPE, etc.)
    char **cmd;                     // Command arguments (e.g., ["ls", "-l"])
    char *file;                     // File for redirection, if applicable
    struct s_ast_node *left;        // Left child (used for piping, AND, OR, etc.)
    struct s_ast_node *right;       // Right child (used for piping, AND, OR, etc.)
} t_ast_node;


typedef struct s_process {
    pid_t pid;         
    int status;   
    int pipe_fd[2];  
    int input_fd;       
    int output_fd;       
} t_process;

typedef struct s_exec_env {
    char **envp;          
    int exit_status; 
} t_exec_env;


typedef struct s_redirect {
    int type;         // Type of redirection (e.g., input, output, append)
    char *file;     
} t_redirect;


typedef struct s_parser {
    char *input;        // Raw input from the user
    t_ast_node *ast;    // Root of the AST generated from input
} t_parser;


void print_error(char * message);
void execute_cd(char *path);
void execute_pwd();
void execute_exit();
void execute_unset(char ***envp, char *var_name);

#endif