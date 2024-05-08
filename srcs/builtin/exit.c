/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:55:48 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 15:33:48 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_in_ascii(char *err)
{
	int	i;

	i = 0;
	while (err[i])
	{
		if (!(err[i] >= '0' && err[i] <= '9'))
			return (1);
		++i;
	}
	return (0);
}

void	ft_exit(char *err)
{
	char	num;

	if (err != NULL)
	{
		num = (char)ft_atoi((const char *)err);
		if (ft_strlen(err) > 12 || ft_check_in_ascii(err))
		{
			write(2, "exit: ", 6);
			write(2, err, ft_strlen(err));
			write(2, ":numeric argument required\n", 36);
			g_mini.exit_code = 255;
			exit(255);
		}
		g_mini.exit_code = num;
		exit(g_mini.exit_code);
	}
	exit(g_mini.exit_code);
}
