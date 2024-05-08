/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:25:13 by pjang             #+#    #+#             */
/*   Updated: 2022/12/27 15:17:01 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	left_pipe(t_tree *t, int fd[])
{
	dup2(g_mini.fd[WRITE], STDOUT_FILENO);
	close(g_mini.fd[READ]);
	close(g_mini.fd[WRITE]);
	visit(t->left, fd);
	exit(g_mini.exit_code);
}

void	right_pipe(t_tree *t, int fd[])
{
	dup2(g_mini.fd[READ], STDIN_FILENO);
	close(g_mini.fd[WRITE]);
	close(g_mini.fd[READ]);
	visit(t->right, fd);
	exit(g_mini.exit_code);
}

void	do_pipe(t_tree *t, int fd[])
{
	int		status;
	pid_t	pid;
	int		temp;

	if (pipe(g_mini.fd) == -1)
		put_error2(strerror(errno), "pipe");
	g_mini.is_child = 1;
	set_signal();
	pid = fork();
	if (pid == 0)
		left_pipe(t, fd);
	close(g_mini.fd[WRITE]);
	pid = fork();
	if (pid == 0)
		right_pipe(t, fd);
	close(g_mini.fd[READ]);
	waitpid(pid, &status, 0);
	while (wait(&temp) != -1)
		;
	g_mini.exit_code = status;
}
