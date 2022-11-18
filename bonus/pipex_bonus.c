/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:50:44 by francisco         #+#    #+#             */
/*   Updated: 2022/11/18 16:44:58 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	handle_pipes(t_data *data, char **argv, int i)
{
	if (i == 2)
	{
		data->infile = open(argv[i - 1], O_RDONLY);
		if (data->infile < 0)
			msg_error(ERR_INFILE);
		dup2(data->infile, STDIN_FILENO);
		dup2(data ->fd[1], STDOUT_FILENO);
		close(data->infile);
	}
	if (i > 2 && argv[i + 2] == NULL)
	{
		data->outfile = open(argv[i + 1], O_TRUNC | O_CREAT | O_RDWR, 0666);
		if (data->outfile < 0)
			msg_error(ERR_OUTFILE);
		dup2(data->store_fd, STDIN_FILENO);
		dup2(data->outfile, STDOUT_FILENO);
		close(data->outfile);
	}
	if (i > 2 && argv[i + 2] != NULL)
	{
		dup2(data->store_fd, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
	}
}

void	childp(t_data *data, char **argv, int i)
{
	data->pid[i - 2] = fork();
	if (data->pid[i - 2] == 0)
	{
		handle_pipes(data, argv, i);
		data->store_fd = dup(data->fd[0]);
		close_pipe(data->fd);
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

	if (argc < 5)
		return (msg(ERR_INPUT));
	data = ft_calloc(sizeof(t_data), 1);
	data->envp = envp;
	data->paths = get_paths(data->envp);
	if (!data->paths)
		return (msg(ERR_PATHS));
	data->pid = ft_calloc(argc - 2, sizeof(int));
	i = 2;
	while (i < argc - 2)
	{
		if (pipe(data->fd) < 0)
			msg_error(ERR_PIPE);
		data->args = get_args(argv[i], data->paths);
		childp(data, argv, i);
		close_pipe(data->fd);
		free_split(data->args);
		i++;
	}
	i = 0;
	while (data->pid[i])
		waitpid(data->pid[i++], NULL, 0);
	free (data->pid);
	free_split(data->paths);
}