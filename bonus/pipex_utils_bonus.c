/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 23:37:01 by francisco         #+#    #+#             */
/*   Updated: 2022/11/18 15:36:52 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

int	check_char(char *arg, char c)
{
	char	*temp;
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == c)
		{
			temp = ft_strjoin("./", arg);
			free(arg);
			arg = ft_strdup(temp);
			free(temp);
			return (1);
		}
		i++;
	}
	return (0);
}

int	try_paths(char *path, char **args)
{
	char	*temp1;
	char	*temp2;

	if (args[0][0] == '/' || args[0][0] == '.')
		return (1);
	if (check_char(args[0], '/') == 1)
		return (1);
	temp1 = ft_strjoin(path, "/");
	temp2 = ft_strjoin(temp1, args[0]);
	if (access(temp2, F_OK) == 0)
	{
		free(temp2);
		temp2 = ft_strdup(args[0]);
		free(args[0]);
		args[0] = ft_strjoin(temp1, temp2);
		free(temp1);
		free(temp2);
		return (1);
	}
	free(temp1);
	free(temp2);
	return (0);
}
