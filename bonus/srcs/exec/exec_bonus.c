/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:57:48 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 21:32:54 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	refresh_exit_code(int status)
{
	if (WIFEXITED(status))
		g_mini.exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_mini.exit_code = WTERMSIG(status);
	g_mini.is_child = 0;
}

void	is_minishell(char **cmd)
{
	if (!ft_strcmp(cmd[0], "./minishell") || !ft_strcmp(cmd[0], "minishell"))
		g_mini.is_minishell = 1;
	else
		g_mini.is_minishell = 0;
}

void	exec_cmd(char **cmd)
{
	char	*path;
	pid_t	pid;
	int		status;
	char	**env;

	path = real_path(cmd);
	if (!path)
		return ;
	env = convert_lst_2d(g_mini.env);
	if (!env)
		return ;
	is_minishell(cmd);
	pid = fork();
	if (pid == 0)
	{
		g_mini.is_child = 1;
		set_signal();
		if (execve(path, cmd, env) < 0)
			put_error3(strerror(errno), cmd[0]);
	}
	waitpid(pid, &status, 0);
	refresh_exit_code(status);
	safety_dimention_free(env);
	safety_free((void **)&path);
	set_signal();
}

void	do_command(char	*tok)
{
	char	*tmp;
	char	**cmd;
	int		idx;
	int		i;

	cmd = ft_split_flag(tok, ' ');
	if (!cmd)
		return ;
	idx = is_asterisk(cmd);
	i = -1;
	while (cmd[++i])
	{
		tmp = ft_strdup_flag(cmd[i]);
		ft_swap_p_char(&tmp, &cmd[i]);
		free(tmp);
	}
	if (idx >= 1 || ((idx == 0) && (cmd[1] == NULL)))
		exec_asterisk(cmd, idx);
	else if (is_builtin2(cmd[0]))
		exec_builtin(cmd);
	else
		exec_cmd(cmd);
	safety_dimention_free(cmd);
}
