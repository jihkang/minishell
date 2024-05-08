/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:56:59 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 21:37:50 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(char *str)
{
	t_list	*fnd;

	if (str == NULL)
		return ;
	fnd = find_lst(g_mini.env, str);
	if (fnd != NULL)
	{
		if (fnd->next)
		{
			fnd->next->prev = fnd->prev;
		}
		if (fnd->prev)
		{
			fnd->prev->next = fnd->next;
		}
		free_node(&fnd);
	}
	g_mini.exit_code = 0;
}
