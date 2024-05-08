/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:35:32 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 16:05:33 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

char	*get_replace_str(t_tkn *tkn1, t_tkn *tkn2)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(tkn1->value, " ");
	res = ft_strjoin(temp, tkn2->value);
	safety_free((void **)&temp);
	return (res);
}

void	refresh_token_list(t_list **list1, t_list **list2)
{
	t_list	*part1;
	t_list	*part2;

	part1 = *list1;
	part2 = *list2;
	part1->next = part2->next;
	if (part2->next)
		part2->next->prev = part1;
}

void	join_list(int a, int b)
{
	char	*replace;
	t_tkn	*tkn;
	t_list	*part1;
	t_list	*part2;

	part1 = g_mini.token;
	while (a-- > 0)
		part1 = part1->next;
	part2 = g_mini.token;
	while (b-- > 0)
		part2 = part2->next;
	replace = get_replace_str(part1->content, part2->content);
	tkn = (t_tkn *)part1->content;
	safety_free((void **)&tkn->value);
	tkn->value = replace;
	refresh_token_list(&part1, &part2);
	ft_lstdelone(part2, &free_tkn);
}

void	join_command(int **sort_idx, int i)
{
	int	j;
	int	a;
	int	b;

	while (1)
	{
		sort_idx[0] = sort_redirection_idx();
		j = i;
		while (sort_idx[0][++i] != -1)
			if (sort_idx[0][i] == 1)
				break ;
		a = j;
		while (sort_idx[0][++a] != -1 && a < i)
			if (sort_idx[0][a] == 3)
				break ;
		b = a;
		while (sort_idx[0][++b] != -1 && b < i)
			if (sort_idx[0][b] == 3)
				break ;
		if ((a < b) && (b != i))
			join_list(a, b);
		if (sort_idx[0][i] == -1)
			break ;
		safety_free((void **)&sort_idx[0]);
	}
}

void	right_arrange_token(int i)
{
	int		*sort_idx;

	if (ft_lstsize(g_mini.token) == 1)
		return ;
	if (get_max_redirection_count())
	{
		i = -1;
		while (++i <= ft_lstsize(g_mini.token))
		{
			sort_idx = sort_redirection_idx();
			swap_token(sort_idx);
			safety_free((void **)&sort_idx);
		}
	}
	if (get_max_command_count())
	{
		i = -1;
		while (++i <= ft_lstsize(g_mini.token))
		{
			join_command(&sort_idx, -1);
			safety_free((void **)&sort_idx);
		}
	}
}
