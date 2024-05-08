/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:45:20 by pjang             #+#    #+#             */
/*   Updated: 2022/12/27 14:57:36 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*add_node(void *content)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	lst->content = content;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

t_list	*last_lst(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	push_back_lst(t_list **lst, void *content)
{
	t_list	*node;
	t_list	*last;

	last = last_lst(*lst);
	node = add_node(content);
	if (last == NULL)
	{
		*lst = node;
		return ;
	}
	last->next = node;
	node->prev = last;
}

t_list	*find_lst(t_list *lst, char *key)
{
	t_env	*env;

	if (lst == NULL)
		return (NULL);
	while (lst)
	{
		env = lst->content;
		if (ft_strcmp(get_key(env), key) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	replace_lst(t_list **lst, void *content)
{
	t_list	*find;
	t_list	*node;

	find = find_lst(*lst, get_key(content));
	if (find == NULL)
		return (push_back_lst(lst, content));
	node = add_node(content);
	node->next = find->next;
	node->prev = find->prev;
	if (node->prev == NULL)
		(*lst) = node;
	else
		node->prev->next = node;
	if (node->next)
		node->next->prev = node;
	free_node(&find);
}
