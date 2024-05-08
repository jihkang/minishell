/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:47:22 by pjang             #+#    #+#             */
/*   Updated: 2022/11/24 14:51:12 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strichr(char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			break ;
		str++;
		i++;
	}
	return (i);
}

int	ft_strcmp(char *str, char *str2)
{
	while (*str && *str2)
	{
		if (*str != *str2)
			return (*str - *str2);
		str++;
		str2++;
	}
	return (*str - *str2);
}
