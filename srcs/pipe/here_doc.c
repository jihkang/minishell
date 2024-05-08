/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:24:22 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 16:08:17 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unlink_tmp_in_here_doc(char *filename)
{
	if (unlink(filename) == -1)
		put_error2(strerror(errno), "unlink");
}

void	input_here_doc_redirection(char *filename)
{
	int	tmp;

	tmp = open(filename, O_RDONLY, 0644);
	if (tmp == -1)
		put_error(strerror(errno), filename);
	if (dup2(tmp, STDIN_FILENO) == -1)
		put_error(strerror(errno), "dup2 here_doc");
	if (close(tmp) == -1)
		put_error(strerror(errno), "close here_doc");
}

void	gnl_child(char *buf, char *get, char *limiter, int fd)
{
	char	*tmp;

	while (1)
	{
		get = readline(">");
		if (get == NULL)
		{
			safety_free((void **)&buf);
			break ;
		}
		if (ft_strcmp(get, limiter) == 0)
		{
			safety_free((void **)&get);
			if (buf != NULL)
			{
				ft_putendl_fd(buf, fd);
				safety_free((void **)&buf);
			}
			break ;
		}
		tmp = buf;
		buf = ft_strjoin_char(buf, get, '\n');
		safety_free((void **)&tmp);
		safety_free((void **)&get);
	}
}

void	read_gnl(char *limiter, int fd)
{
	char			*get;
	char			*buf;

	g_mini.is_heredoc = 1;
	set_signal();
	dup2(0, 55);
	gnl_child(buf = NULL, get = NULL, limiter, fd);
	g_mini.is_heredoc = 0;
	dup2(55, 0);
	close(55);
}

int	here_doc(char *limiter)
{
	int		fd;
	char	*filename;

	if (limiter == NULL)
		return (-1);
	if (ft_memcmp("\"\"", limiter, 3) == 0)
		limiter = ft_strdup("");
	filename = get_heredoc_filename(g_mini.tmp_count);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		put_error(strerror(errno), filename);
		return (1);
	}
	read_gnl(limiter, fd);
	g_mini.is_unlink = 1;
	if (*limiter == '\0')
		safety_free((void **)&limiter);
	return (0);
}
