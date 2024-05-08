/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:54:19 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 15:45:32 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

char	*ft_astric(char *path)
{
	char			*o_path;
	char			*o_name;
	int				i;

	i = ft_strrchr2(path, '/');
	o_path = get_path2(path, i + 1);
	if (o_path == NULL)
		o_path = getcwd(NULL, 0);
	o_name = get_file(path + i + 1);
	if (o_name == NULL)
	{
		free(o_path);
		return (NULL);
	}
	return (ft_astric_sub(o_path, o_name));
}

int	read_direct(char *path, char *file)
{
	struct dirent	*item;
	DIR				*p_dir;

	p_dir = opendir(path);
	if (!p_dir)
		return (-1);
	while (42)
	{
		item = readdir(p_dir);
		if (item == NULL)
			break ;
		if (ft_strcmp(file, item->d_name) == 0)
		{
			closedir(p_dir);
			return (0);
		}
	}
	closedir(p_dir);
	return (-1);
}

int	ft_access(char *path)
{
	char	*o_path;
	char	*o_name;
	int		i;
	int		res;

	i = ft_strrchr2(path, '/');
	o_path = get_path2(path, i + 1);
	if (o_path == NULL)
		o_path = getcwd(NULL, 0);
	o_name = get_file(path + i + 1);
	if (o_name == NULL)
	{
		free(o_path);
		return (-1);
	}
	res = read_direct(o_path, o_name);
	free(o_path);
	free(o_name);
	return (res);
}
