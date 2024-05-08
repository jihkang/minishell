/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:08:49 by pjang             #+#    #+#             */
/*   Updated: 2023/01/05 14:39:56 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parsing(char *buf, int fd[])
{
	t_prs	prs;

	init_prs(&prs);
	do_priority(buf, &prs);
	divide_quote(buf, &prs);
	divide_pts(&prs);
	divide_logical(&prs);
	divide_pipe(&prs);
	divide_redirection(&prs);
	if (valid_token_list(&prs))
		return ;
	get_token_array(&prs);
	get_token_list();
	right_arrange_token(0);
	change_env();
	do_priority(buf, &prs);
	in_tree(&prs);
	free_prs(&prs);
	do_heredoc(g_mini.tree, fd);
	g_mini.tmp_count = 1;
}

void	do_priority2(char *buf, t_prs *prs, int *i)
{
	if (is_seq((buf + *i)))
		prs->priority[*i] = is_seq((buf + *i));
	else if (is_seq1((buf + *i)))
		prs->priority[*i] = is_seq1((buf + *i));
	else if (is_seq2((buf + *i)))
		prs->priority[*i] = is_seq2((buf + *i));
	else if (is_seq3((buf + *i)))
		prs->priority[*i] = is_seq3((buf + *i));
	else if (buf[*i] != ' ')
		prs->priority[*i] = COMMAND;
	if (prs->priority[*i] == AND || prs->priority[*i] == OR || \
		prs->priority[*i] == HEREDOC || prs->priority[*i] == STD_OUTA)
	{
		*i += 1;
	}
}

void	do_priority(char *buf, t_prs *prs)
{
	int	i;

	safety_free((void **)&prs->priority);
	prs->priority = (char *)malloc(sizeof(char) * (ft_strlen(buf) + 1));
	if (!prs->priority)
		exit(1);
	ft_memset((void *)prs->priority, ' ', ft_strlen(buf));
	i = -1;
	while (buf[++i])
		do_priority2(buf, prs, &i);
	prs->priority[i] = '\0';
}

char	*get_content(char *buf, t_prs *prs)
{
	int		i;
	char	*res;

	i = prs->s_e[START];
	while (buf[i])
	{
		if (ft_isspace(buf[i]) != ' ')
		{
			prs->s_e[START] = i;
			break ;
		}
		i++;
	}
	i = prs->s_e[END];
	while (i >= prs->s_e[START])
	{
		if (ft_isspace(buf[i]) != ' ')
		{
			prs->s_e[END] = i;
			break ;
		}
		i--;
	}
	res = ft_substr(buf, prs->s_e[START], prs->s_e[END] - prs->s_e[START] + 1);
	return (res);
}

void	into_list(char *buf, t_prs *prs, int no)
{
	char	*content;

	content = get_content(buf, prs);
	if (no == 1)
		ft_lstadd_back(&prs->quote, ft_lstnew((void *)content));
	else if (no == 2)
		ft_lstadd_back(&prs->pts, ft_lstnew((void *)content));
	else if (no == 3)
		ft_lstadd_back(&prs->logical, ft_lstnew((void *)content));
	else if (no == 4)
		ft_lstadd_back(&prs->pipe, ft_lstnew((void *)content));
	else if (no == 5)
		ft_lstadd_back(&prs->redirect, ft_lstnew((void *)content));
}
