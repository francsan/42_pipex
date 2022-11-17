/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 23:37:01 by francisco         #+#    #+#             */
/*   Updated: 2022/11/17 00:08:21 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

void	sort_arg(char *arg)
{
	int		i;
	int		j;
	char	*temp;

	i = ft_strlen(arg) - 1;
	j = 0;
	while (arg[i] != '/')
	{
		j++;
		i--;
	}
	i++;
	temp = ft_calloc(j + 1, sizeof(char));
	j = 0;
	while (arg[i])
		temp[j++] = arg[i++];
	free(arg);
	arg = ft_strdup(temp);
	free (temp);
}

int	try_paths(char *path, char **args)
{
	char	*temp1;
	char	*temp2;

	if (args[0][0] == '/')
		sort_arg(args[0]);
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
