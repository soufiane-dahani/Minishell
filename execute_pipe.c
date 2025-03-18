/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/03/18 01:39:42 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	**resize_commands(t_ast_node **commands, size_t cmd_count)
{
	t_ast_node	**new_temp;

	new_temp = ft_calloc(cmd_count + 1, sizeof(t_ast_node *));
	if (!new_temp)
		return (NULL);
	ft_memcpy(new_temp, commands, cmd_count * sizeof(t_ast_node *));
	// Free the old memory
	free(commands);
	return (new_temp);
}

void	process_commands(t_ast_node *current, t_ast_node ***commands,
		int *cmd_count)
{
	t_ast_node	**temp;

	while (current)
	{
		if (current->type == PIPE)
		{
			// Check if left node exists and is a command
			if (current->left && current->left->type == SIMPLE_CMD)
			{
				temp = resize_commands(*commands, *cmd_count);
				if (!temp)
				{
					perror("calloc failed");
					free(*commands);
					exit(EXIT_FAILURE);
				}
				*commands = temp;
				(*commands)[(*cmd_count)++] = current->left;
			}
			// Move to right child (next pipe or command)
			if (current->right)
			{
				if (current->right->type == SIMPLE_CMD)
				{
					temp = resize_commands(*commands, *cmd_count);
					if (!temp)
					{
						perror("calloc failed");
						free(*commands);
						exit(EXIT_FAILURE);
					}
					*commands = temp;
					(*commands)[(*cmd_count)++] = current->right;
					break ;
				}
				current = current->right;
			}
			else
			{
				break ;
			}
		}
		else if (current->type == SIMPLE_CMD)
		{
			temp = resize_commands(*commands, 1);
			if (!temp)
			{
				perror("calloc failed");
				free(*commands);
				exit(EXIT_FAILURE);
			}
			*commands = temp;
			(*commands)[(*cmd_count)++] = current;
			break ;
		}
		else
		{
			break ;
		}
	}
}

// Function to create pipes and allocate memory for PIDs
int	**create_pipes_and_pids(int cmd_count, t_ast_node **commands, pid_t **pids)
{
	int	num_pipes;
	int	**pipes;
	int	i;

	num_pipes = cmd_count - 1;
	if (cmd_count < 2)
	{
		free(commands);
		return (NULL);
	}
	pipes = malloc(num_pipes * sizeof(int *));
	if (!pipes)
	{
		perror("malloc failed");
		free(commands);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < num_pipes)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i])
		{
			perror("malloc failed");
			while (i-- > 0)
				free(pipes[i]);
			free(pipes);
			free(commands);
			exit(EXIT_FAILURE);
		}
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe failed");
			while (i-- >= 0)
				free(pipes[i]);
			free(pipes);
			free(commands);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	*pids = malloc(cmd_count * sizeof(pid_t));
	if (!*pids)
	{
		perror("malloc failed");
		i = 0;
		while (i < num_pipes)
			free(pipes[i++]);
		free(pipes);
		free(commands);
		exit(EXIT_FAILURE);
	}
	return (pipes);
}

// Function to execute commands using fork and pipe redirection
void	execute_commands(int cmd_count, t_ast_node **commands, int **pipes,
		pid_t *pids, char **envp)
{
	int		num_pipes;
	int		i;
	int		j;
	char	**argv;
			char *path;

	num_pipes = cmd_count - 1;
	i = 0;
	while (i < cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork failed");
			j = 0;
			while (j < num_pipes)
				free(pipes[j++]);
			free(pipes);
			free(commands);
			free(pids);
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
		{ // Child process
			if (i > 0 && dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
			{
				perror("dup2 failed for stdin");
				exit(EXIT_FAILURE);
			}
			if (i < num_pipes && dup2(pipes[i][1], STDOUT_FILENO) == -1)
			{
				perror("dup2 failed for stdout");
				exit(EXIT_FAILURE);
			}
			j = 0;
			while (j < num_pipes)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			// Extract the command arguments
			argv = commands[i]->cmd;
			if (!argv || !argv[0])
			{
				write(2, "error: command not found\n", 25);
				exit(127);
			}
			// Resolve the command path
			if (strchr(argv[0], '/'))
				path = argv[0];
			else
				path = find_path(argv[0], envp);
			if (!path)
			{
				write(2, "error: command not found\n", 25);
				exit(127);
			}
			execve(path, argv, envp);
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

// Main function to execute the pipeline
void	execute_pipe(t_ast_node *node, char **envp)
{
	int			cmd_count;
	t_ast_node	**commands;
	pid_t		*pids;
	int			**pipes;
	int			num_pipes;
	int			j;
		int status;
	int			i;

	cmd_count = 0;
	commands = NULL;
	// Flatten the AST to get all commands in order
	process_commands(node, &commands, &cmd_count);
	// Create pipes and allocate memory for PIDs
	pipes = create_pipes_and_pids(cmd_count, commands, &pids);
	if (!pipes)
	{
		print_error("Pipe creation failed\n");
		return ;
	}
	execute_commands(cmd_count, commands, pipes, pids, envp);
	// Close pipes
	num_pipes = cmd_count - 1;
	j = 0;
	while (j < num_pipes)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	// Wait for all child processes
	j = 0;
	while (j < cmd_count)
	{
		waitpid(pids[j], &status, 0);
		j++;
	}
	// Free allocated memory
	i = 0;
	while (i < num_pipes)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	free(commands);
	free(pids);
}

void	error(void)
{
	perror("Error");
	exit(126);
}
