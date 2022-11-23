/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 23:37:01 by francisco         #+#    #+#             */
/*   Updated: 2022/11/22 04:23:55 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	close_pipe(t_data *data)
{
	close(data->pipe[0]);
	close(data->pipe[1]);
}

int	sort_arg(t_data *data)
{
	char	*temp;

	if (data->args[0][0] == '/' || data->args[0][0] == '.')
	{
		if (access(data->args[0], F_OK) == 0)
		{
			data->arg = strdup(data->args[0]);
			return (1);
		}
	}
	else
	{
		temp = ft_strjoin("./", data->args[0]);
		data->arg = ft_strdup(temp);
		free(temp);
		return (1);
	}
	return (0);
}

int	check_char(t_data *data)
{
	int		j;

	j = -1;
	while (data->args[0][++j])
	{
		if (data->args[0][j] == '/')
			return (1);
	}
	return (0);
}

int	try_paths(t_data *data, int j)
{
	char	*temp1;
	char	*temp2;

	if (check_char(data))
		return (sort_arg(data));
	temp1 = ft_strjoin(data->paths[j], "/");
	temp2 = ft_strjoin(temp1, data->args[0]);
	if (access(temp2, F_OK) == 0)
	{
		data->arg = strdup(temp2);
		free(temp1);
		free(temp2);
		return (1);
	}
	free(temp1);
	free(temp2);
	return (0);
}
