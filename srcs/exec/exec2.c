/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:00:46 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 16:12:41 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_builtin(char	**cmd)
{
	if (!(ft_strcmp(cmd[0], "echo")))
	{
		if (cmd[1] && !(ft_strcmp(cmd[1], "-n")))
			ft_echo(&cmd[1], 0);
		else
			ft_echo(cmd, 1);
	}
	else if (!(ft_strcmp(cmd[0], "cd")))
		ft_cd(cmd[1]);
	else if (!(ft_strcmp(cmd[0], "pwd")))
		ft_pwd();
	else if (!(ft_strcmp(cmd[0], "export")))
		ft_export(cmd[1]);
	else if (!(ft_strcmp(cmd[0], "unset")))
	{
		ft_unset(cmd[1]);
	}
	else if (!(ft_strcmp(cmd[0], "env")))
		ft_env();
	else if (!(ft_strcmp(cmd[0], "exit")))
		ft_exit(cmd[1]);
}

int	is_builtin2(char	*cmd)
{
	if (!(ft_strcmp(cmd, "cd")) || !(ft_strcmp(cmd, "echo")))
		return (1);
	if (!(ft_strcmp(cmd, "pwd")) || !(ft_strcmp(cmd, "export")))
		return (1);
	if (!(ft_strcmp(cmd, "unset")) || !(ft_strcmp(cmd, "env")))
		return (1);
	if (!(ft_strcmp(cmd, "exit")))
		return (1);
	return (0);
}
