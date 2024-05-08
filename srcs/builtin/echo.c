/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:24:10 by jihkang           #+#    #+#             */
/*   Updated: 2023/01/03 21:55:31 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **split, int flag)
{
	int		i;
	int		j;

	i = 1;
	while (split != NULL && split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (split[i][j] == '\\' && flag != 1)
			{
				if (split[i][j + 1] == split[i][j])
					write(1, "\\", 1);
			}
			else
				write(1, &split[i][j], 1);
			++j;
		}
		if (split[i + 1] != NULL)
			write(1, " ", 1);
		++i;
	}
	if (split != NULL && flag == 1)
		write(1, "\n", 1);
}
