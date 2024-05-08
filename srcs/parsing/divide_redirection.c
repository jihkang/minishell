/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:56:48 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 15:12:58 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_one_redirect_idx(char *buf, t_prs *prs, int *i, int *flag)
{
	int	j;

	j = 1;
	if (buf[*i + 1] == ' ')
	{
		while (buf[*i + j] == ' ')
			j++;
		*flag = 1;
	}
	else
		*flag = 2;
	if (*i > prs->s_e[START])
	{
		prs->s_e[END] = *i - 1;
		into_list(buf, prs, 5);
	}
	prs->s_e[START] = *i;
	prs->s_e[END] = *i;
	into_list(buf, prs, 5);
	prs->s_e[START] = *i + j;
	if (*flag == 1)
		*i += j;
}

void	set_two_redirect_idx(char *buf, t_prs *prs, int *i, int *flag)
{
	int	j;

	j = 2;
	if (buf[*i + 2] == ' ')
	{
		while (buf[*i + j] == ' ')
			j++;
		*flag = 1;
	}
	else
		*flag = 2;
	if (*i > prs->s_e[START])
	{
		prs->s_e[END] = *i - 1;
		into_list(buf, prs, 5);
	}
	prs->s_e[START] = *i;
	prs->s_e[END] = *i + 1;
	into_list(buf, prs, 5);
	prs->s_e[START] = *i + j;
	if (*flag == 1)
		*i += j;
	else if (*flag == 2)
		*i += 1;
}

void	set_filename_idx(char *buf, t_prs *prs, int i, int *flag)
{
	int	j;

	j = *flag;
	j += 1;
	if (j == 3)
	{
		*flag = 0;
		prs->s_e[END] = i - 1;
		into_list(buf, prs, 5);
		prs->s_e[START] = i + 1;
	}
}

void	divide_redirection2(char *buf, t_prs *prs)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	prs->s_e[START] = 0;
	prs->s_e[END] = 0;
	while (prs->priority[++i])
	{
		if (!flag && prs->priority[i] == STD_IN)
			set_one_redirect_idx(buf, prs, &i, &flag);
		else if (!flag && prs->priority[i] == HEREDOC)
			set_two_redirect_idx(buf, prs, &i, &flag);
		else if (!flag && prs->priority[i] == STD_OUTT)
			set_one_redirect_idx(buf, prs, &i, &flag);
		else if (!flag && prs->priority[i] == STD_OUTA)
			set_two_redirect_idx(buf, prs, &i, &flag);
		else if (flag && buf[i] == ' ')
			set_filename_idx(buf, prs, i, &flag);
	}
	if (buf[prs->s_e[END]] != '\0' && buf[prs->s_e[START]] != '\0')
	{
		prs->s_e[END] = i;
		into_list(buf, prs, 5);
	}
}

void	divide_redirection(t_prs *prs)
{
	char	*cg;
	t_list	*temp;

	temp = prs->pipe;
	while (temp)
	{
		cg = (char *)temp->content;
		if (is_quote(cg))
		{
			ft_lstadd_back(&prs->redirect, ft_lstnew(ft_strdup(cg)));
			temp = temp->next;
			continue ;
		}
		do_priority(cg, prs);
		divide_redirection2(cg, prs);
		temp = temp->next;
	}
}
