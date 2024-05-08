/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:08:11 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 19:36:56 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tkn	*new_tkn(int idx, char *value)
{
	t_tkn	*new;

	if (!value)
		return (NULL);
	new = (t_tkn *)malloc(sizeof(t_tkn));
	new->idx = idx;
	new->value = ft_strdup(value);
	return (new);
}

void	get_token_array(t_prs *prs)
{
	int		i;
	char	*buf;
	t_list	*temp;

	temp = prs->redirect;
	init_tkn(temp);
	i = 0;
	while (temp)
	{
		buf = (char *)temp->content;
		if (set_logical_pipe_token(buf, i))
			;
		else if (set_redirection_token(temp, buf, i))
		{
			i++;
			temp = temp->next;
			if (!temp)
				break ;
		}
		else
			set_command_token(&temp, buf, &i);
		i++;
		temp = temp->next;
	}
}

void	get_token_list(void)
{
	int	i;

	i = 0;
	while (g_mini.tkn[i].idx != -1)
	{
		if (g_mini.tkn[i].idx == 0)
		{
			i++;
			continue ;
		}
		ft_lstadd_back(&g_mini.token, \
			ft_lstnew((void *)new_tkn(g_mini.tkn[i].idx, g_mini.tkn[i].value)));
		i++;
	}
}

void	swap_token(int *sort_idx)
{
	int	i;
	int	j;
	int	a;
	int	b;

	i = -1;
	while (1)
	{
		j = i;
		while (sort_idx[++i] != -1)
			if (sort_idx[i] == 1)
				break ;
		a = j;
		while (sort_idx[++a] != -1 && a < i)
			if (sort_idx[a] == 3 && sort_idx[a + 1] != 3)
				break ;
		b = a - 1;
		while (sort_idx[++b] != -1 && b < i)
			if (sort_idx[b] == 2)
				break ;
		if ((a < b) && (b != i))
			swap_list(a, b);
		if (sort_idx[i] == -1)
			break ;
	}
}

int	*sort_redirection_idx(void)
{
	int		len;
	int		*res;
	t_tkn	*tkn;
	t_list	*temp;

	res = (int *)malloc(sizeof(int) * (ft_lstsize(g_mini.token) + 1));
	if (!res)
		return (NULL);
	len = 0;
	temp = g_mini.token;
	while (temp)
	{
		tkn = (t_tkn *)temp->content;
		if (tkn->idx == AND || tkn->idx == OR || tkn->idx == PIPE)
			res[len] = 1;
		if (tkn->idx == STD_IN || tkn->idx == STD_OUTT || \
			tkn->idx == HEREDOC || tkn->idx == STD_OUTA)
			res[len] = 2;
		if (tkn->idx == COMMAND)
			res[len] = 3;
		len++;
		temp = temp->next;
	}
	res[len] = -1;
	return (res);
}
