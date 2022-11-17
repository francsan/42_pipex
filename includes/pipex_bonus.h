/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 00:26:14 by francisco         #+#    #+#             */
/*   Updated: 2022/11/17 01:16:19 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/* errors */

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PATHS "Couldn't find paths.\n"
# define ERR_PIPE "Pipe"
# define ERR_CMD "command not found: "

/* pipex_bonus functions */

//pipex_bonus.c
void	handle_pipes(char **argv, int i, int *fd, int store_fd);
void	childp(char **argv, int i, int *fd, char **args);
char	**get_paths(char **envp);
char	**get_args(char *argv, char **paths);

//pipex_utils_bonus.c
void	close_pipe(int *fd);
void	free_split(char **strs);
int		sort_arg(char *arg);
int		try_paths(char *path, char **args);

//pipex_errors_bonus.c
int		msg(char *error);
void	msg_error(char *error);
void	msg_cmd_error(char *error, char *cmd);

/* libft functions */

//ft_strlen.c
size_t	ft_strlen(const char *s);

//ft_strncmp.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//ft_strjoin.c
char	*ft_strjoin(char const *s1, char const *s2);

//ft_strlcpy.c
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

//ft_strdup.c
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
