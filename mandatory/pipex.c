/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francsan <francsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:24:47 by francsan          #+#    #+#             */
/*   Updated: 2022/11/23 16:51:04 by francsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	handle_pipes(t_data *data, char **argv)
{
	if (data->i == 2)
	{
		data->infile = open(argv[1], O_RDONLY);
		if (data->infile < 0)
			msg_error(ERR_INFILE);
		dup2(data->pipe[1], STDOUT_FILENO);
		dup2(data->infile, STDIN_FILENO);
		close(data->infile);
	}
	if (data->i == 3)
	{
		data->outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0666);
		if (data->outfile < 0)
			msg_error(ERR_OUTFILE);
		dup2(data->outfile, STDOUT_FILENO);
		dup2(data->pipe[0], STDIN_FILENO);
		close(data->outfile);
	}
	close_pipe(data);
}

void	childp(t_data *data, char **argv, char **envp)
{
	data->pid = fork();
	if (data->pid < 0)
		msg_error(ERR_FORK);
	else if (data->pid == 0)
	{
		handle_pipes(data, argv);
		if (data->arg == NULL)
			msg_cmd_error(data->args[0]);
		execve(data->arg, data->args, envp);
		exit(0);
	}
}

int	get_args(t_data *data, char **argv)
{
	int	j;

	data->args = ft_split(argv[data->i], ' ');
	j = -1;
	while (data->paths[++j])
	{
		if (try_paths(data, j))
			return (1);
	}
	data->arg = NULL;
	return (-1);
}

int	get_paths(t_data *data, char **envp)
{
	int		j;

	j = -1;
	while (envp[++j])
	{
		if (ft_strncmp(envp[j], "PATH=", 5) == 0)
		{
			data->paths = ft_split(&envp[j][5], ':');
			return (1);
		}
	}
	return (-1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 5)
		return (msg(ERR_INPUT));
	data = ft_calloc(sizeof(t_data), 1);
	if (!get_paths(data, envp))
		return (msg(ERR_PATHS));
	if (pipe(data->pipe) < 0)
		msg_error(ERR_PIPE);
	data->i = 1;
	while (++(data->i) <= argc - 2)
	{
		get_args(data, argv);
		childp(data, argv, envp);
		free_split(data->args);
		free(data->arg);
	}
	close_pipe(data);
	waitpid(-1, NULL, 0);
	free_split(data->paths);
	free(data);
}
