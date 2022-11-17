/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:24:47 by francsan          #+#    #+#             */
/*   Updated: 2022/11/17 00:12:01 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	handle_pipes(char **argv, int i, int *fd)
{
	int	file;

	if (i == 2)
	{
		file = open(argv[i - 1], O_RDONLY);
		if (file < 0)
			msg_error(ERR_INFILE);
		dup2(fd[1], STDOUT_FILENO);
		dup2(file, STDIN_FILENO);
	}
	if (i == 3)
	{
		file = open(argv[i + 1], O_TRUNC | O_CREAT | O_RDWR, 0666);
		if (file < 0)
			msg_error(ERR_OUTFILE);
		dup2(file, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
	}
	close_pipe(fd);
	close(file);
}

void	childp(char **argv, int i, int *fd, char **args)
{
	int	pid;

	if (i == 3 && fd[0] < 0)
		exit(0);
	pid = fork();
	if (pid == 0)
	{
		handle_pipes(argv, i, fd);
		if (args[0] == NULL)
			msg_cmd_error(ERR_CMD, argv[i]);
		execve(args[0], args, NULL);
		waitpid(pid, NULL, 0);
		exit(0);
	}
}

char	**get_args(char *argv, char **paths)
{
	char	**args;
	int		i;

	args = ft_split(argv, ' ');
	i = 0;
	while (paths[i])
	{
		if (try_paths(paths[i], args) == 1)
			return (args);
		i++;
	}
	free(args[0]);
	args[0] = NULL;
	return (args);
}

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(&envp[i][5], ':');
			return (paths);
		}
		i++;
	}
	return (paths);
}

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	char	**args;
	int		fd[2];
	int		i;

	if (argc != 5)
		return (msg(ERR_INPUT));
	paths = get_paths(envp);
	if (!paths)
		return (msg(ERR_PATHS));
	if (pipe(fd) < 0)
		msg_error(ERR_PIPE);
	i = 2;
	while (i <= 3)
	{
		args = get_args(argv[i], paths);
		childp(argv, i, fd, args);
		free_split(args);
		i++;
	}
	close_pipe(fd);
	free_split(paths);
	return (0);
}
