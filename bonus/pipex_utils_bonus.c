/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 23:37:01 by francisco         #+#    #+#             */
/*   Updated: 2022/11/11 15:52:59 by francisco        ###   ########.fr       */
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

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			paths = ft_split(&envp[i][5], ':');
		i++;
	}
	return (paths);
}

void	free_temps(char *temp1, char *temp2, char **args)
{
	free(temp2);
	temp2 = ft_strdup(args[0]);
	free(args[0]);
	args[0] = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
}

char	**get_args(char *argv, char **paths)
{
	char	**args;
	char	*temp1;
	char	*temp2;
	int		i;

	args = ft_split(argv, ' ');
	i = 0;
	while (paths[i])
	{
		temp1 = ft_strjoin(paths[i], "/");
		temp2 = ft_strjoin(temp1, args[0]);
		if (access(temp2, F_OK) == 0)
		{
			free_temps(temp1, temp2, args);
			return (args);
		}
		free(temp1);
		free(temp2);
		i++;
	}
	free(args[0]);
	args[0] = NULL;
	return (args);
}
