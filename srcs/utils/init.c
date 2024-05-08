/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:49:27 by pjang             #+#    #+#             */
/*   Updated: 2022/12/22 21:54:00 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_mini(void)
{
	g_mini.continue_flag = 0;
	g_mini.pts_flag = 0;
	g_mini.pts_exist = 0;
	g_mini.exit_code = 0;
	g_mini.is_minishell = 0;
	g_mini.is_heredoc = 0;
	g_mini.is_unlink = 0;
	g_mini.tmp_count = 1;
	g_mini.env = NULL;
	g_mini.tkn = NULL;
	g_mini.token = NULL;
	g_mini.tree = NULL;
	g_mini.heredoc = ft_lstnew((void *)ft_strdup("tmp.heredoc1"));
	g_mini.tree_idx = NULL;
	g_mini.contents = NULL;
}

void	init_tkn(t_list *temp)
{
	int		i;
	int		len;

	len = ft_lstsize(temp);
	g_mini.tkn = (t_tkn *)malloc(sizeof(t_tkn) * (len + 1));
	if (!g_mini.tkn)
		put_error(strerror(errno), "init malloc");
	i = 0;
	while (i < len)
	{
		g_mini.tkn[i].idx = 0;
		g_mini.tkn[i].value = NULL;
		i++;
	}
	g_mini.tkn[len].idx = -1;
	g_mini.tkn[len].value = NULL;
}

void	init_prs(t_prs *prs)
{
	prs->priority = NULL;
	prs->quote = NULL;
	prs->pts = NULL;
	prs->logical = NULL;
	prs->pipe = NULL;
	prs->redirect = NULL;
}
