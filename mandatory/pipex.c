/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:24:47 by francsan          #+#    #+#             */
/*   Updated: 2022/11/18 14:29:10 by francisco        ###   ########.fr       */
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

void	childp(t_data *data, char **argv, int i)
{
	data->pid[i - 2] = fork();
	if (data->pid[i - 2] == 0)
	{
		handle_pipes(argv, i, data->fd);
		if (data->args[0] == NULL)
			msg_cmd_error(argv[i]);
		execve(data->args[0], data->args, data->envp);
		exit(0);
	}
}

char	**get_args(char *arg, char **paths)
{
	char	**args;
	int		i;

	args = ft_split(arg, ' ');
	i = 0;
	while (paths[i])
	{
		if (try_paths(paths[i], args))
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
	t_data	*data;
	int		i;

	if (argc != 5)
		return (msg(ERR_INPUT));
	data = ft_calloc(sizeof(t_data), 1);
	data->envp = envp;
	data->paths = get_paths(data->envp);
	if (!data->paths)
		return (msg(ERR_PATHS));
	if (pipe(data->fd) < 0)
		msg_error(ERR_PIPE);
	data->pid = ft_calloc(argc - 2, sizeof(int));
	i = 2;
	while (i <= 3)
	{
		data->args = get_args(argv[i], data->paths);
		childp(data, argv, i);
		free_split(data->args);
		i++;
	}
	close_pipe(data->fd);
	i = 0;
	while (data->pid[i])
		waitpid(data->pid[i++], NULL, 0);
	free (data->pid);
	free_split(data->paths);
}
