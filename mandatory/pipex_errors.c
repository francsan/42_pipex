/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:45:06 by francisco         #+#    #+#             */
/*   Updated: 2022/11/17 00:21:56 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	msg(char *error)
{
	write(2, error, ft_strlen(error));
	return (1);
}

void	msg_error(char *error)
{
	perror(error);
	exit(1);
}

void	msg_cmd_error(char *error, char *cmd)
{
	char	*temp1;
	char	*temp2;
	int		i;

	i = 0;
	while (cmd[i] != ' ' && cmd[i])
		i++;
	temp1 = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (cmd[i] != ' ' && cmd[i])
	{
		temp1[i] = cmd[i];
		i++;
	}
	temp2 = ft_strjoin(error, temp1);
	free(temp1);
	temp1 = ft_strjoin(temp2, "\n");
	write(2, temp1, ft_strlen(temp1));
	free(temp1);
	free(temp2);
	exit(1);
}
