/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:11:34 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 21:52:08 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_cmd_path(char **envp)
{
	char	**path;
	char	*strs;
	char	**temp;

	temp = envp;
	strs = NULL;
	while (*temp != NULL)
	{
		if (ft_strncmp(*temp, "PATH=", 5) == 0)
		{
			strs = ft_substr(*temp, 5, 1024);
			break ;
		}
		temp++;
	}
	if (!strs)
		return (NULL);
	path = ft_split(strs, ':');
	safety_free((void **)&strs);
	return (path);
}

char	*get_execve_path(char	*cmd, char	**temp)
{
	char	*path;
	char	*p_temp;

	path = NULL;
	while (*temp != NULL)
	{
		safety_free((void **)&path);
		p_temp = ft_strjoin(*temp, "/");
		path = ft_strjoin(p_temp, cmd);
		if (!p_temp || !path)
			put_error("malloc assign error", "getpath");
		safety_free((void **)&p_temp);
		if (!ft_access(path))
			break ;
		temp++;
	}
	return (path);
}

int	real_path2(char **tmp, char **env)
{
	if (!tmp)
	{
		safety_dimention_free(env);
		return (1);
	}
	return (0);
}

char	*real_path(char	**cmd)
{
	char	**env;
	char	**tmp;
	char	*path;

	if (!ft_strchr(cmd[0], '/'))
	{
		env = convert_lst_2d(g_mini.env);
		tmp = get_cmd_path(env);
		if (real_path2(tmp, env))
			return (NULL);
		path = get_execve_path(cmd[0], tmp);
		safety_dimention_free(tmp);
		tmp = NULL;
		safety_dimention_free(env);
		env = NULL;
	}
	else
	{
		path = ft_strdup(cmd[0]);
		if (!path)
			return (NULL);
	}
	return (path);
}
