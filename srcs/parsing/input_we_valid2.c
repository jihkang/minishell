/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_we_valid2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:17:03 by pjang             #+#    #+#             */
/*   Updated: 2022/12/11 20:53:27 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	valid_we2(int *flag, char c, int **count)
{
	if (*flag == 1 && c == '\'')
	{
		*flag = 0;
		count[0][0] += 1;
	}
	else if (*flag == 2 && c == '\"')
	{
		*flag = 0;
		count[0][1] += 1;
	}
	else if (*flag == 3 && c == '`')
	{
		*flag = 0;
		count[0][2] += 1;
	}
}

void	valid_we(int *flag, char c, int **count)
{
	if (!*flag && c == '\'')
	{
		*flag = 1;
		count[0][0] += 1;
		return ;
	}
	else if (!*flag && c == '\"')
	{
		*flag = 2;
		count[0][1] += 1;
		return ;
	}
	else if (!*flag && c == '`')
	{
		*flag = 3;
		count[0][2] += 1;
		return ;
	}
	valid_we2(flag, c, count);
}

int	get_result_valid_we(int *count)
{
	if (count[0] % 2 == 1)
		return (1);
	if (count[1] % 2 == 1)
		return (2);
	if (count[2] % 2 == 1)
		return (3);
	return (0);
}
