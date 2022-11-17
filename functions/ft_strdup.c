/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:57:50 by francsan          #+#    #+#             */
/*   Updated: 2022/11/16 18:15:33 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;

	dup = malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s1, (ft_strlen(s1) + 1));
	return (dup);
}
