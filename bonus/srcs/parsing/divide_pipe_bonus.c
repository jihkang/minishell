/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_pipe_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:30:23 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 16:04:21 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	divide_pipe2(char *buf, t_prs *prs)
{
	int	i;

	i = -1;
	prs->s_e[START] = 0;
	prs->s_e[END] = 0;
	while (prs->priority[++i])
	{
		if (prs->priority[i] == '|')
		{
			if (i > prs->s_e[START])
			{
				prs->s_e[END] = i - 1;
				into_list(buf, prs, 4);
			}
			prs->s_e[START] = i;
			prs->s_e[END] = i;
			into_list(buf, prs, 4);
			prs->s_e[START] = i + 1;
		}
	}
	if (buf[prs->s_e[END]] != '\0' && buf[prs->s_e[START]] != '\0')
	{
		prs->s_e[END] = i;
		into_list(buf, prs, 4);
	}
}

void	divide_pipe(t_prs *prs)
{
	char	*cg;
	t_list	*temp;

	temp = prs->logical;
	while (temp)
	{
		cg = (char *)temp->content;
		if (is_quote(cg))
		{
			ft_lstadd_back(&prs->pipe, ft_lstnew(ft_strdup(cg)));
			temp = temp->next;
			continue ;
		}
		do_priority(cg, prs);
		divide_pipe2(cg, prs);
		temp = temp->next;
	}
}
