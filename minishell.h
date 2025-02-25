/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:04:53 by sodahani          #+#    #+#             */
/*   Updated: 2025/02/23 12:32:29 by sodahani         ###   ########.fr       */
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
    SIMPLE_CMD,   // For simple commands like "ls", "echo"
    PIPE,         // For piping between commands
    REDIRECT_IN,  // For input redirection ("<")
    REDIRECT_OUT, // For output redirection (">")
    APPEND_OUT,   // For output append redirection (">>")
    AND,          // For "&&"
    OR            // For "||"
} t_ast_node_type;

typedef struct s_ast_node {
    t_ast_node_type type;           // The type of the node (e.g., SIMPLE_CMD, PIPE, etc.)
    char **cmd;                     // Command arguments (e.g., ["ls", "-l"])
    char *file;                     // File for redirection, if applicable
    struct s_ast_node *left;        // Left child (used for piping, AND, OR, etc.)
    struct s_ast_node *right;       // Right child (used for piping, AND, OR, etc.)
} t_ast_node;


typedef struct s_process {
    pid_t pid;            // Process ID of the child process
    int status;           // The status of the process (exit status)
    int pipe_fd[2];       // For pipe redirection, store pipe file descriptors
    int input_fd;         // File descriptor for input redirection
    int output_fd;        // File descriptor for output redirection
} t_process;

typedef struct s_exec_env {
    char **envp;           // Environment variables
    int exit_status;       // Exit status of the last executed command
} t_exec_env;


typedef struct s_redirect {
    int type;         // Type of redirection (e.g., input, output, append)
    char *file;       // File to redirect to/from
} t_redirect;


typedef struct s_parser {
    char *input;        // Raw input from the user
    t_ast_node *ast;    // Root of the AST generated from input
} t_parser;


void print_error(char * message);


#endif