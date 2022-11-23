/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:50:44 by francisco         #+#    #+#             */
/*   Updated: 2022/11/22 21:01:17 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	handle_pipes(t_data *data, int argc, char **argv)
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
	if (data->i > 2 && data->i < argc - 2)
	{
		dup2(data->pipe[1], STDOUT_FILENO);
		dup2(data->old_pipe, STDIN_FILENO);
	}
	if (data->i == argc - 2)
	{
		data->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0666);
		if (data->outfile < 0)
			msg_error(ERR_OUTFILE);
		dup2(data->outfile, STDOUT_FILENO);
		dup2(data->old_pipe, STDIN_FILENO);
		close(data->outfile);
	}
	close_pipe(data);
}

void	childp(t_data *data, int argc,  char **argv, char **envp)
{
	data->pid[data->i - 2] = fork();
	if (data->pid[data->i - 2] < 0)
		msg_error(ERR_FORK);
	else if (data->pid[data->i - 2] == 0)
	{
		handle_pipes(data, argc, argv);
		if (data->arg == NULL)
			msg_cmd_error(data->args[0]);
		execve(data->arg, data->args, envp);
		exit(0);
	}
	data->old_pipe = dup(data->pipe[0]);
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

	if (argc < 5)
		return (msg(ERR_PATHS));
	data = ft_calloc(sizeof(t_data), 1);
	if (!get_paths(data, envp))
		return (msg(ERR_PATHS));
	data->pid = ft_calloc(argc - 3, sizeof(pid_t));
	data->i = 1;
	while (++(data->i) <= argc - 2)
	{
		if (pipe(data->pipe) < 0)
			msg_error(ERR_PIPE);
		get_args(data, argv);
		childp(data, argc, argv, envp);
		close_pipe(data);
		free_split(data->args);
		free(data->arg);
	}
	data->i = -1;
	while (data->pid[++(data->i)])
		waitpid(data->pid[data->i], NULL, 0);
	free_split(data->paths);
}
