/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_pts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:53:53 by pjang             #+#    #+#             */
/*   Updated: 2023/01/05 14:21:58 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_pts_open_idx(char *buf, t_prs *prs, int *i, int *flag)
{
	int	j;

	*flag += 1;
	if (*i > prs->s_e[START])
	{
		prs->s_e[END] = *i - 1;
		into_list(buf, prs, 2);
	}
	j = 1;
	while (prs->priority[*i + j] == '(')
	{
		j++;
		*flag += 1;
	}
	prs->s_e[START] = *i + j;
	*i += j - 1;
}

void	set_pts_close_idx(char *buf, t_prs *prs, int *i, int *flag)
{
	int	j;

	*flag -= 1;
	j = 1;
	while (prs->priority[*i + j] == ')')
	{
		j++;
		*flag -= 1;
	}
	if (*i != 0)
	{
		prs->s_e[END] = *i - 1;
		into_list(buf, prs, 2);
	}
	else
		prs->s_e[END] = *i;
	prs->s_e[START] = *i + j;
	*i += j - 1;
}

void	set_pts_finish_idx(char *buf, t_prs *prs, int i)
{
	if (buf[i] == '(' || buf[i] == ')')
	{
		if (i == 0)
			return ;
		prs->s_e[END] = i - 1;
	}
	else
		prs->s_e[END] = i;
	into_list(buf, prs, 2);
}

void	divide_pts2(char *buf, t_prs *prs)
{
	int	i;

	i = -1;
	prs->s_e[START] = 0;
	prs->s_e[END] = 0;
	while (prs->priority[++i])
	{
		if (prs->priority[i] == '(')
			set_pts_open_idx(buf, prs, &i, &g_mini.pts_flag);
		else if (g_mini.pts_flag && prs->priority[i] == ')')
			set_pts_close_idx(buf, prs, &i, &g_mini.pts_flag);
	}
	if (buf[prs->s_e[END]] != '\0' && buf[prs->s_e[START]] != '\0')
		set_pts_finish_idx(buf, prs, i);
}

void	divide_pts(t_prs *prs)
{
	char	*cg;
	t_list	*temp;

	temp = prs->quote;
	while (temp)
	{
		cg = (char *)temp->content;
		if (is_quote(cg))
		{
			ft_lstadd_back(&prs->pts, ft_lstnew(ft_strdup(cg)));
			temp = temp->next;
			continue ;
		}
		do_priority(cg, prs);
		divide_pts2(cg, prs);
		temp = temp->next;
	}
}
