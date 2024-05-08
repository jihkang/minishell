/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:08:11 by pjang             #+#    #+#             */
/*   Updated: 2022/11/22 17:33:57 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	swap_list2(int a, int b)
{
	t_list	*list_a;
	t_list	*before_a;
	t_list	*list_b;
	t_list	*before_b;
	t_list	*temp;

	temp = g_mini.token;
	while (a-- > 1)
		temp = temp->next;
	before_a = temp;
	list_a = before_a->next;
	temp = g_mini.token;
	while (b-- > 1)
		temp = temp->next;
	before_b = temp;
	list_b = before_b->next;
	temp = list_b->next;
	list_b->prev = before_a;
	list_b->next = list_a;
	list_a->prev = list_b;
	list_a->next = temp;
	if (temp)
		temp->prev = list_a;
	before_a->next = list_b;
}

void	swap_list(int a, int b)
{
	t_list	*list_a;
	t_list	*list_b;
	t_list	*before_b;
	t_list	*temp;

	if (a == 0)
	{
		list_a = g_mini.token;
		temp = g_mini.token;
		while (b-- > 1)
			temp = temp->next;
		before_b = temp;
		list_b = before_b->next;
		temp = list_b->next;
		list_b->prev = NULL;
		list_b->next = list_a;
		list_a->prev = list_b;
		list_a->next = temp;
		if (temp)
			temp->prev = list_a;
		g_mini.token = list_b;
	}
	else
		swap_list2(a, b);
}
