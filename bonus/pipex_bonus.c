/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francsan <francsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:24:47 by francsan          #+#    #+#             */
/*   Updated: 2022/11/14 17:06:07 by francsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	handle_pipes(char **argv, int i, int *fd, int store_fd)
{
	int	infile;
	int	outfile;

	if (i == 2)
	{
		infile = open(argv[i - 1], O_RDONLY);
		dup2(fd[1], STDOUT_FILENO);
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (argv[i + 2] == NULL)
	{
		outfile = open(argv[i + 1], O_TRUNC | O_CREAT | O_RDWR);
		dup2(outfile, STDOUT_FILENO);
		dup2(store_fd, STDIN_FILENO);
		close(outfile);
	}
	if (i > 2 && argv[i + 2] != NULL)
	{
		dup2(store_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
}

int	childp(char **argv, int i, int *fd, char **args)
{
	static int	store_fd;
	int			pid;

	if (i > 2 && !store_fd)
		return (0);
	pid = fork();
	if (pid == 0)
	{
		handle_pipes(argv, i, fd, store_fd);
		close(fd[0]);
		close(fd[1]);
		if (args[0] != NULL)
			execve(args[0], args, NULL);
		waitpid(pid, NULL, 0);
	}
	store_fd = dup(fd[0]);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	char	**args;
	int		fd[2];
	int		i;

	if (argc >= 5)
	{
		paths = get_paths(envp);
		if (!paths)
			return (0);
		i = 2;
		while (argv[i + 1] != NULL)
		{
			if (pipe(fd) == -1)
				return (0);
			args = get_args(argv[i], paths);
			childp(argv, i, fd, args);
			free_split(args);
			close(fd[0]);
			close(fd[1]);
			i++;
		}
		free_split(paths);
	}
}
