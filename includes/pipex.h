/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francsan <francsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:18:34 by francisco         #+#    #+#             */
/*   Updated: 2022/11/23 16:51:09 by francsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/* errors */

# define ERR_INFILE "infile"
# define ERR_OUTFILE "outfile"
# define ERR_INPUT "invalid number of arguments.\n"
# define ERR_PATHS "couldn't find paths.\n"
# define ERR_PIPE "pipe"
# define ERR_FORK "fork failed"
# define ERR_CMD1 "command not found: "
# define ERR_CMD2 "no such file or directory: "

/* struct */
typedef struct s_data
{
	char	**paths;
	char	**args;
	char	*arg;
	int		pipe[2];
	int		i;
	int		infile;
	int		outfile;
	pid_t	pid;
}	t_data;

/* pipex functions */

//pipex.c
void	handle_pipes(t_data *data, char **argv);
void	childp(t_data *data, char **argv, char **envp);
int		get_args(t_data *data, char **argv);
int		get_paths(t_data *data, char **envp);

//pipex_utils.c
void	free_split(char **strs);
void	close_pipe(t_data *data);
int		sort_arg(t_data *data);
int		check_char(t_data *data);
int		try_paths(t_data *data, int j);

//pipex_errors.c
int		msg(char *error);
void	msg_error(char *error);
void	msg_cmd_error(char *cmd);

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
