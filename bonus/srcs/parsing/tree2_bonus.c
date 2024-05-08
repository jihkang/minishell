/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:36:15 by pjang             #+#    #+#             */
/*   Updated: 2023/01/05 14:00:04 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	set_res_idx_pts2(char token, int **t_idx, int *seq, int res)
{
	int	i;
	int	j;

	if (token == AND || token == OR)
		j = 10;
	if (token == PIPE)
		j = 20;
	if (token == STD_IN || token == STD_OUTT || \
		token == HEREDOC || token == STD_OUTA)
		j = 30;
	i = -1;
	while (t_idx[0][++i] != -1)
	{
		if (t_idx[0][i] == j)
			seq[(int)token]--;
		if (seq[(int)token] == 0)
		{
			t_idx[0][i] = j - res;
			break ;
		}
	}
}

void	set_res_idx_pts(t_prs *prs, int **t_idx)
{
	int		i;
	int		seq[130];
	int		res;
	char	token;

	if (g_mini.pts_exist)
	{
		i = -1;
		ft_memset(seq, 0, sizeof(int) * 130);
		res = 0;
		while (prs->priority[++i])
		{
			token = prs->priority[i];
			if (res && (token == AND || token == OR || token == PIPE || \
				token == STD_IN || token == STD_OUTT || \
				token == HEREDOC || token == STD_OUTA))
			{
				res = is_ptscount(prs->priority, i);
				seq[(int)token]++;
				set_res_idx_pts2(token, t_idx, seq, res);
				res = 0;
			}
		}
	}
}

int	get_res_idx_pts(t_tkn *tkn)
{
	if (tkn->idx == AND || tkn->idx == OR)
		return (10);
	if (tkn->idx == PIPE)
		return (20);
	if (tkn->idx == STD_IN || tkn->idx == STD_OUTT || \
		tkn->idx == HEREDOC || tkn->idx == STD_OUTA)
		return (30);
	if (tkn->idx == COMMAND)
		return (40);
	return (0);
}

int	get_res_idx_normal(t_tkn *tkn)
{
	if (tkn->idx == AND || tkn->idx == OR)
		return (1);
	if (tkn->idx == PIPE)
		return (2);
	if (tkn->idx == STD_IN || tkn->idx == STD_OUTT || \
		tkn->idx == HEREDOC || tkn->idx == STD_OUTA)
		return (3);
	if (tkn->idx == COMMAND)
		return (4);
	return (0);
}

int	*get_tree_idx(t_prs *prs)
{
	int		len;
	int		*res;
	t_tkn	*tkn;
	t_list	*temp;

	(void)prs;
	len = ft_lstsize(g_mini.token);
	res = (int *)malloc(sizeof(int) * (len + 1));
	if (!res)
		put_error2(strerror(errno), "malloc");
	len = 0;
	temp = g_mini.token;
	while (temp)
	{
		tkn = (t_tkn *)temp->content;
		if (g_mini.pts_exist)
			res[len] = get_res_idx_pts(tkn);
		else
			res[len] = get_res_idx_normal(tkn);
		len++;
		temp = temp->next;
	}
	res[len] = -1;
	set_res_idx_pts(prs, &res);
	return (res);
}
