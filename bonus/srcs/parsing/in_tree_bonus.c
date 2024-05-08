/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_tree_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:31:26 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 16:04:40 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	get_priority_idx2(int depth, int *i, int right, int n)
{
	while ((*i) < right)
	{
		if (g_mini.tree_idx[*i] == depth)
		{
			g_mini.tree_idx[*i] = n;
			break ;
		}
		*i += 1;
	}
}

void	get_priority_idx(int depth, int left, int right, int n)
{
	int	i;
	int	limit;

	if (g_mini.pts_exist)
		limit = 41;
	else
		limit = 5;
	if (depth >= limit)
		return ;
	if (left < right)
	{
		i = left;
		get_priority_idx2(depth, &i, right, n);
		if (i == right)
			get_priority_idx(depth + 1, left, right, n);
		else
		{
			get_priority_idx(depth + 1, left, i, 2 * n);
			get_priority_idx(depth, i + 1, right, 2 * n + 1);
		}
	}
}

int	get_max_idx(void)
{
	int	res;
	int	len;

	len = 0;
	while (len < ft_lstsize(g_mini.token))
	{
		if (len == 0)
			res = g_mini.tree_idx[len];
		else
			res = ft_max(res, g_mini.tree_idx[len]);
		len++;
	}
	return (res);
}

void	add_tree_phase(int i, int idx)
{
	t_tkn	*tkn;
	t_list	*temp;

	temp = g_mini.token;
	while (temp && --i > 0)
		temp = temp->next;
	tkn = (t_tkn *)temp->content;
	add_tree(&g_mini.tree, idx, new_tree(tkn->idx, ft_strdup(tkn->value)), -1);
}

void	in_tree(t_prs *prs)
{
	int		i;
	int		idx;
	int		flag;

	g_mini.tree_idx = get_tree_idx(prs);
	get_priority_idx(1, 0, ft_lstsize(g_mini.token), 1);
	idx = 1;
	while (idx <= get_max_idx())
	{
		flag = 0;
		i = 0;
		while (i < ft_lstsize(g_mini.token) && g_mini.tree_idx[i] != -1)
		{
			if (g_mini.tree_idx[i++] == idx)
			{
				flag = 1;
				break ;
			}
		}
		if (flag)
			add_tree_phase(i, idx);
		idx++;
	}
	safety_free((void **)&g_mini.tree_idx);
}
