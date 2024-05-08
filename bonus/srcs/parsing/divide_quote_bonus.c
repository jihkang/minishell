/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_quote_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:30:57 by pjang             #+#    #+#             */
/*   Updated: 2023/01/05 13:26:52 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	is_token(char c)
{
	if (c == '&' || c == '|' || c == '<' || c == '>' || c == '(' || c == ')')
		return (1);
	return (0);
}

void	set_quote_open_idx(char *buf, t_prs *prs, int i)
{
	int	j;

	j = 1;
	while (i && buf[i - j] != ' ' && !is_token(buf[i - j]))
		j++;
	if (i > prs->s_e[START])
	{
		prs->s_e[END] = i - j;
		into_list(buf, prs, 1);
	}
	prs->s_e[START] = i - j + 1;
}

void	set_quote_close_idx(char *buf, t_prs *prs, int *i, int *flag)
{
	int	j;
	int	q_flag;

	q_flag = 0;
	j = 1;
	while (buf[*i + j] && (buf[*i + j] != ' ' || q_flag) && \
		!is_token(buf[*i + j]))
	{
		if (buf[*i + j] == '\"' || buf[*i + j] == '\'')
			q_flag = 1;
		j++;
		get_flag_match(&q_flag, buf[*i + j], NULL, &j);
	}
	*flag = 0;
	prs->s_e[END] = *i + j - 1;
	into_list(buf, prs, 1);
	prs->s_e[START] = *i + j;
	if (buf[*i + j])
		*i += j;
	else
		*i += j - 1;
}

void	init_quote_val(int *i, int *flag, t_prs *prs)
{
	*i = -1;
	*flag = 0;
	prs->s_e[START] = 0;
	prs->s_e[END] = 0;
}

void	divide_quote(char *buf, t_prs *prs)
{
	int	i;
	int	flag;

	init_quote_val(&i, &flag, prs);
	while (prs->priority[++i])
	{
		if (!flag && prs->priority[i] == '\"')
		{
			flag = 1;
			set_quote_open_idx(buf, prs, i);
		}
		else if (!flag && prs->priority[i] == '\'')
		{
			flag = 2;
			set_quote_open_idx(buf, prs, i);
		}
		else if (flag == 1 && prs->priority[i] == '\"')
			set_quote_close_idx(buf, prs, &i, &flag);
		else if (flag == 2 && prs->priority[i] == '\'')
			set_quote_close_idx(buf, prs, &i, &flag);
	}
	if (buf[prs->s_e[END]] == '\0' || buf[prs->s_e[START]] == '\0')
		return ;
	prs->s_e[END] = i;
	into_list(buf, prs, 1);
}
