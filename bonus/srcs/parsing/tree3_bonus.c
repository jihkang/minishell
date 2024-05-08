/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree3_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:47:31 by pjang             #+#    #+#             */
/*   Updated: 2023/01/05 13:56:58 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	is_ptscount(char *str, int i)
{
	int	idx;
	int	res;

	if (!str)
		return (0);
	res = 0;
	idx = 0;
	while (idx < i && str[idx])
	{
		if (str[idx] == ')')
			res++;
		idx++;
	}
	return (res);
}
