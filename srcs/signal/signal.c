/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 21:01:39 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 16:08:28 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler(int signal)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (pid == -1)
	{
		if (signal == SIGINT)
		{
			if (g_mini.is_heredoc && signal == SIGINT)
			{
				write(1, "\0", 1);
				close(0);
				return ;
			}
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 1);
			rl_redisplay();
		}
		if (signal == SIGQUIT && g_mini.is_heredoc)
			return ;
		return ;
	}
	if (g_mini.is_minishell == 0 && signal == SIGINT)
		write(1, "\n", 1);
}

void	set_signal(void)
{
	if (g_mini.is_child == 0)
		rl_catch_signals = 0;
	else
		rl_catch_signals = 1;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
