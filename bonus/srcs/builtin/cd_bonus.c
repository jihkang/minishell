/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:34:24 by pjang             #+#    #+#             */
/*   Updated: 2022/12/27 15:26:18 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static void	ft_cd_free(char *str, char *str2, char *str3)
{
	free(str);
	free(str2);
	free(str3);
}

int	ft_cd_home(char *old, char *remain)
{
	t_list	*home;
	char	*pwd;
	char	*path;
	int		mv;

	if (remain != NULL)
		remain += (*remain == '~');
	home = find_lst(g_mini.env, "HOME");
	if (!home)
		return (-1);
	path = ft_strjoin(get_value(home->content), remain);
	pwd = ft_strjoin_char("PWD", path, '=');
	mv = chdir(path);
	if (mv != -1)
	{
		ft_export(old);
		ft_export(pwd);
		free(old);
	}
	free(path);
	free(pwd);
	return (mv);
}

void	ft_cd(char *path)
{
	int		mv;
	char	*remove_path;
	char	*pwd;
	char	*old;

	mv = -1;
	remove_path = ft_pwd2();
	old = ft_strjoin_char("OLDPWD", remove_path, '=');
	free(remove_path);
	if ((path == NULL || *path == 0 || *path == '~') && \
		ft_cd_home(old, path) != -1)
		return ;
	else if (path != NULL && *path != 0)
		mv = chdir(path);
	if (mv == -1)
	{
		free(old);
		write(2, "error move\n", 11);
		return ;
	}
	remove_path = ft_pwd2();
	pwd = ft_strjoin_char("PWD", remove_path, '=');
	ft_export(old);
	ft_export(pwd);
	ft_cd_free(old, remove_path, pwd);
}
