/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:02:36 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 16:24:36 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strrchr2(char *str, char c)
{
	int	i;

	if (str == NULL || *str == 0)
		return (-1);
	i = 0;
	while (*str && str[i])
		++i;
	--i;
	while (i >= 0 && str[i])
	{
		if (str[i] == c)
			return (i);
		--i;
	}
	return (-1);
}

char	*get_path2(char *str, int r)
{
	if (str == NULL || *str == 0)
		return (NULL);
	if (r == 0)
		return (NULL);
	if (str[r - 1] == '/')
		return (ft_substr(str, 0, r - 1));
	return (ft_substr(str, 0, r));
}

char	*get_file(char *str)
{
	if (str == NULL || *str == 0)
		return (NULL);
	return (ft_strdup(str));
}

char	*ft_astric_sub2(DIR *p_dir, char *ret, char *o_name)
{
	struct dirent	*item;
	char			*temp;

	while (42)
	{
		item = readdir(p_dir);
		if (item == NULL)
			break ;
		if (!ft_strcmp(item->d_name, ".") || !ft_strcmp(item->d_name, ".."))
			continue ;
		if (ft_match(item->d_name, o_name))
		{
			temp = ret;
			ret = ft_strjoin_char(temp, item->d_name, ' ');
			safety_free((void **)&temp);
		}
	}
	return (ret);
}

char	*ft_astric_sub(char *o_path, char *o_name)
{
	DIR		*p_dir;
	char	*ret;

	p_dir = opendir(o_path);
	if (!p_dir)
	{
		safety_free((void **)&o_name);
		safety_free((void **)&o_path);
		return (NULL);
	}
	ret = ft_astric_sub2(p_dir, ret = NULL, o_name);
	safety_free((void **)&o_name);
	safety_free((void **)&o_path);
	closedir(p_dir);
	return (ret);
}
