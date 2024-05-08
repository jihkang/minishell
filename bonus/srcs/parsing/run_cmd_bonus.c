/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:34:09 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 16:14:55 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	init_stdfd(int *fd_in, int *fd_out, int *fd_err)
{
	*fd_in = -1;
	*fd_out = -1;
	*fd_err = -1;
}

void	back_up_stdfd(int *fd_in, int *fd_out, int *fd_err, int n)
{
	if (n == 1)
	{
		*fd_in = dup(STDIN_FILENO);
		*fd_out = dup(STDOUT_FILENO);
		*fd_err = dup(STDERR_FILENO);
	}
	if (n == 2)
	{
		dup2(*fd_in, STDIN_FILENO);
		dup2(*fd_out, STDOUT_FILENO);
		dup2(*fd_err, STDERR_FILENO);
	}
	if (n == 3)
	{
		dup2(*fd_in, STDIN_FILENO);
		dup2(*fd_out, STDOUT_FILENO);
		dup2(*fd_err, STDERR_FILENO);
		close(*fd_in);
		close(*fd_out);
		close(*fd_err);
	}
}

int	input_valid(char **buf)
{
	int		num;
	char	*temp;

	temp = *buf;
	num = input_we_valid(*buf);
	if (!num)
	{
		safety_free((void **)buf);
		return (num);
	}
	num = input_bash_valid(*buf);
	if (*temp == '#')
	{
		safety_free((void **)buf);
		return (0);
	}
	if (!num)
		safety_free((void **)buf);
	return (num);
}

int	do_signal(char **buf)
{
	add_history(*buf);
	if (!*buf)
	{
		printf("\033[1A");
		printf("\033[12C");
		printf("exit\n");
		safety_free((void **)&*buf);
		g_mini.is_minishell = 0;
		exit(1);
	}
	return (1);
}

void	run_cmd(char *buf)
{
	int		fd[3];

	init_stdfd(&fd[0], &fd[1], &fd[2]);
	while (1)
	{
		buf = readline("minishell > ");
		if (do_signal(&buf) && *buf == '\0')
		{
			safety_free((void **)&buf);
			continue ;
		}
		if (!input_valid(&buf))
			continue ;
		back_up_stdfd(&fd[0], &fd[1], &fd[2], 1);
		parsing(buf, fd);
		if (g_mini.continue_flag)
		{
			unlink_command("temp", 2, &buf);
			g_mini.continue_flag = 0;
			continue ;
		}
		visit(g_mini.tree, fd);
		unlink_command("temp", 2, &buf);
		back_up_stdfd(&fd[0], &fd[1], &fd[2], 3);
	}
}
