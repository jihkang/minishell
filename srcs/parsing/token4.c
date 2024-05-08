/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:50:14 by pjang             #+#    #+#             */
/*   Updated: 2022/12/22 21:37:07 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tkn2(void *tkn)
{
	t_tkn	*temp;

	if (tkn)
	{
		temp = (t_tkn *)tkn;
		temp->idx = 0;
		safety_free((void **)&temp->value);
	}
}

void	clear_tkn(t_tkn **tkn, void (*del)(void *))
{
	int		i;
	t_tkn	*temp;

	if (*tkn)
	{
		temp = *tkn;
		i = 0;
		while (temp[i].idx != -1)
			del(&temp[i++]);
		safety_free((void **)tkn);
	}
}

int	get_token_list_idx(int idx)
{
	int		i;
	t_tkn	*tkn;
	t_list	*temp;

	i = -1;
	temp = g_mini.token;
	while (++i < idx)
		temp = temp->next;
	tkn = (t_tkn *)temp->content;
	return (tkn->idx);
}

int	devide_command(char *c, char **str, int *flag, int *i)
{
	int		idx;
	char	*buf;

	idx = is_seq2(c);
	buf = *str;
	if ((*c == '\"' || *c == '\'') && *i == 0)
	{
		*flag = 1;
		return (1);
	}
	if (idx == AND || idx == OR || \
		is_seq3(c) == HEREDOC || is_seq3(c) == STD_OUTA)
	{
		*(buf) = *(c);
		*(buf + 1) = *(c + 1);
		*str += 2;
		return (0);
	}
	if (idx == PIPE || is_seq3(c) == STD_IN || is_seq3(c) == STD_OUTT)
	{
		*buf = *(c);
		*str += 1;
		return (0);
	}
	return (1);
}

int	devide_command2(char *c, int *flag, int *i)
{
	int		idx;

	idx = is_seq2(c);
	if (idx == AND || idx == OR || \
		is_seq3(c) == HEREDOC || is_seq3(c) == STD_OUTA)
	{
		*i += 2;
		return (0);
	}
	if (idx == PIPE || is_seq3(c) == STD_IN || is_seq3(c) == STD_OUTT)
	{
		*i += 1;
		return (0);
	}
	if ((*c == '\"' || *c == '\'') && !*flag)
	{
		*flag = 1;
		return (1);
	}
	return (1);
}
