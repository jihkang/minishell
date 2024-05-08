/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:55:59 by pjang             #+#    #+#             */
/*   Updated: 2022/12/27 15:26:35 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	free_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	free_node(t_list **cur)
{
	free_env((*cur)->content);
	(*cur)->content = NULL;
	free(*cur);
	*cur = NULL;
}

void	clear_envlst(t_list **lst)
{
	t_list	*cur;

	while (*lst)
	{
		cur = *lst;
		(*lst) = (*lst)->next;
		free_node(&cur);
	}
}
