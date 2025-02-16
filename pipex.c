/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:21:27 by sodahani          #+#    #+#             */
/*   Updated: 2025/02/16 14:56:25 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0644);
	if (file == -1)
		error();
	return (file);
}

static void	process_here_doc(int argc, char **argv, char **envp)
{
	int	i;
	int	fileout;

	i = 3;
	fileout = open_file(argv[argc - 1], 0);
	here_doc(argv[2], argc);
	while (i < argc - 2)
		child_process(argv[i++], envp);
	dup2(fileout, STDOUT_FILENO);
	close(fileout);
	execute(argv[argc - 2], envp);
}

static void	process_regular_files(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;
	int	fileout;

	i = 2;
	filein = open_file(argv[1], 2);
	fileout = open_file(argv[argc - 1], 1);
	dup2(filein, STDIN_FILENO);
	close(filein);
	while (i < argc - 2)
		child_process(argv[i++], envp);
	dup2(fileout, STDOUT_FILENO);
	close(fileout);
	execute(argv[argc - 2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc > 5)
			process_here_doc(argc, argv, envp);
		else if (ft_strncmp(argv[1], "here_doc", 8) != 0)
			process_regular_files(argc, argv, envp);
	}
	usage();
	return (1);
}
