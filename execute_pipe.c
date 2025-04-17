/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/17 11:42:42 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	**resize_commands(t_ast **commands, size_t cmd_count)
{
	t_ast	**new_temp;

	new_temp = ft_calloc(cmd_count + 1, sizeof(t_ast *));
	if (!new_temp)
		return (NULL);
	ft_memcpy(new_temp, commands, cmd_count * sizeof(t_ast *));
	free(commands);
	return (new_temp);
}

void	process_commands(t_ast *current, t_ast ***commands, int *cmd_count)
{
	t_ast	**temp;

	while (current)
	{
		if (current->type == TYP_PIPE)  // Corrected for TYP_PIPE
		{
			if (current->l && current->l->type == TYP_WORD)  // Check with TYP_WORD (or SIMPLE_CMD if that’s what you want to use)
			{
				temp = resize_commands(*commands, *cmd_count);
				if (!temp)
				{
					perror("calloc failed");
					free(*commands);
					exit(EXIT_FAILURE);
				}
				*commands = temp;
				(*commands)[(*cmd_count)++] = current->l;  // Corrected for 'l' and 'r'
			}
			if (current->r)  // Use 'r' here as well
			{
				if (current->r->type == TYP_WORD)  // Check with TYP_WORD (or SIMPLE_CMD if needed)
				{
					temp = resize_commands(*commands, *cmd_count);
					if (!temp)
					{
						perror("calloc failed");
						free(*commands);
						exit(EXIT_FAILURE);
					}
					*commands = temp;
					(*commands)[(*cmd_count)++] = current->r;  // Corrected for 'r' and 'l'
					break ;
				}
				current = current->r;  // Corrected for 'r' and 'l'
			}
			else
			{
				break ;
			}
		}
		else if (current->type == TYP_WORD)  // Check with TYP_WORD (or SIMPLE_CMD if needed)
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

int	**create_pipes_and_pids(int cmd_count, t_ast **commands, pid_t **pids)
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

int	execute_commands(int cmd_count, t_ast **commands, int **pipes, pid_t *pids, char **envp)
{
	int		num_pipes;
	int		i;
	int		j;
	char	**argv;
	char	*path;

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
		{
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
			argv = commands[i]->cmd;
			if (!argv || !argv[0])
			{
				write(2, "error: command not found\n", 25);
				exit(127);
			}
			if (strchr(argv[0], '/'))
				path = argv[0];
			else
				path = find_path(argv[0], envp);
			if (!path)
			{
				//write(2, "error: command not found\n", 25);
				exit(127);
			}
			execve(path, argv, envp);
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return 0; // Ensure the function returns an integer value
}

// Main function to execute the pipeline
int	execute_pipe(t_ast *node, char **envp)
{
	int			cmd_count;
	t_ast	**commands;
	pid_t		*pids;
	int			**pipes;
	int			num_pipes;
	int			j;
	int			status;
	int			i;

	cmd_count = 0;
	commands = NULL;
	process_commands(node, &commands, &cmd_count);
	pipes = create_pipes_and_pids(cmd_count, commands, &pids);
	if (!pipes)
	{
		print_error("Pipe creation failed\n");
		return 1; // Return error if pipes creation fails
	}
	execute_commands(cmd_count, commands, pipes, pids, envp);
	num_pipes = cmd_count - 1;
	j = 0;
	while (j < num_pipes)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	j = 0;
	while (j < cmd_count)
	{
		waitpid(pids[j], &status, 0);
		j++;
	}
	i = 0;
	while (i < num_pipes)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	free(commands);
	free(pids);
	return 0; // Return 0 for success
}

void	error(void)
{
	perror("Error");
	exit(126);
}

