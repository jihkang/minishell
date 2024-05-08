/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:35:23 by pjang             #+#    #+#             */
/*   Updated: 2022/12/27 15:26:51 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

char	*ft_pwd2(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	return (pwd);
}

char	*ft_pwd(void)
{
	char	*pwd;
	t_list	*path;

	path = find_lst(g_mini.env, "PWD");
	if (!path)
		return (NULL);
	pwd = get_value(path->content);
	printf("%s\n", pwd);
	return (pwd);
}
