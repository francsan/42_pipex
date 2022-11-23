/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:45:06 by francisco         #+#    #+#             */
/*   Updated: 2022/11/22 04:03:11 by francisco        ###   ########.fr       */
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

void	msg_cmd_error(char *cmd)
{
	char	*temp1;
	char	*temp2;

	if (cmd[0] == '/')
		temp1 = ft_strjoin(ERR_CMD2, cmd);
	else
		temp1 = ft_strjoin(ERR_CMD1, cmd);
	temp2 = ft_strjoin(temp1, "\n");
	write(2, temp2, ft_strlen(temp2));
	free(temp1);
	free(temp2);
	exit(1);
}
