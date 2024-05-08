/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:55:48 by pjang             #+#    #+#             */
/*   Updated: 2022/12/27 15:26:30 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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
		exit(num);
	}
	exit(g_mini.exit_code);
}
