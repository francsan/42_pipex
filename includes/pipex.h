/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:18:34 by francisco         #+#    #+#             */
/*   Updated: 2022/11/11 17:36:01 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

//pipex.c
void	handle_pipe(char **argv, int i, int *fd);
void	childp(char **argv, int i, int *fd, char **args);

//pipex_utils.c
void	free_split(char **strs);
char	**get_paths(char **envp);
char	**get_args(char *argv, char **paths);

//str_utils.c
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);

//ft_split.c
int		mem_size(char const *s, char c);
int		word_size(const char *s, char c);
char	**fill_strs(char **strs, const char *s, char c);
char	**ft_split(char const *s, char c);

//ft_calloc.c
void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);

#endif
