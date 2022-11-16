/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francsan <francsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:14:42 by francsan          #+#    #+#             */
/*   Updated: 2022/11/14 17:05:14 by francsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	handle_pipe(char **argv, int i, int *fd)
{
	int	file;

	if (i == 2)
	{
		file = open(argv[i - 1], O_RDONLY);
		dup2(fd[1], STDOUT_FILENO);
		dup2(file, STDIN_FILENO);
		close(file);
	}
	if (i == 3)
	{
		file = open(argv[i + 1], O_TRUNC | O_CREAT | O_RDWR);
		dup2(file, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
	}
	close(file);
}

void	childp(char **argv, int i, int *fd, char **args)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		handle_pipe(argv, i, fd);
		close(fd[0]);
		close(fd[1]);
		if (args[0] != NULL)
			execve(args[0], args, NULL);
		waitpid(pid, NULL, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	char	**args;
	int		fd[2];
	int		i;

	if (argc == 5)
	{
		paths = get_paths(envp);
		if (!paths)
			return (0);
		if (pipe(fd) == -1)
			return (0);
		i = 2;
		while (i < argc - 1)
		{
			args = get_args(argv[i], paths);
			childp(argv, i, fd, args);
			free_split(args);
			i++;
		}
		close(fd[0]);
		close(fd[1]);
		free_split(paths);
	}
}
