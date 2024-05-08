/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety_free_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:41:39 by pjang             #+#    #+#             */
/*   Updated: 2022/12/27 15:56:08 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	free_tkn(void *tkn)
{
	t_tkn	*temp;

	if (tkn)
	{
		temp = (t_tkn *)tkn;
		temp->idx = 0;
		safety_free((void **)&temp->value);
		safety_free((void **)&temp);
	}
}

void	free_mini(void)
{
	g_mini.tmp_count = 1;
	ft_lstclear(&g_mini.token, &free_tkn);
	ft_lstclear(&g_mini.heredoc, &free);
	g_mini.heredoc = ft_lstnew((void *)ft_strdup("tmp.heredoc1"));
	g_mini.tmp_count = 1;
	clear_tkn(&g_mini.tkn, &free_tkn2);
	safety_free((void **)&g_mini.contents);
	clear_tree(&g_mini.tree, &safety_free);
}

void	free_prs(t_prs *prs)
{
	safety_free((void **)&prs->priority);
	ft_lstclear(&prs->quote, &free);
	ft_lstclear(&prs->pts, &free);
	ft_lstclear(&prs->logical, &free);
	ft_lstclear(&prs->pipe, &free);
	ft_lstclear(&prs->redirect, &free);
}

void	safety_free(void **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	safety_dimention_free(char **strs)
{
	char	**temp;

	if (strs)
	{
		temp = strs;
		while (*strs != NULL)
		{
			if (*strs)
				free(*strs);
			*strs++ = NULL;
		}
		strs = temp;
		free(strs);
		strs = NULL;
	}
}
