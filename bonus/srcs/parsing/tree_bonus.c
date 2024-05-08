/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:36:02 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 16:05:39 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	clear_tree(t_tree **t, void (*del)(void **))
{
	if (is_garbage_node(*t))
	{
		clear_tree(&(*t)->left, del);
		clear_tree(&(*t)->right, del);
		(*t)->key = 0;
		del((void **)&(*t)->value);
		del((void **)t);
	}
}

t_tree	*new_tree(int key, char *value)
{
	t_tree	*new_tree;

	new_tree = (t_tree *)malloc(sizeof(t_tree) * 1);
	if (!new_tree)
		put_error2(strerror(errno), "malloc");
	ft_memset(new_tree, 0, sizeof(t_tree));
	new_tree->key = key;
	new_tree->value = value;
	new_tree->left = NULL;
	new_tree->right = NULL;
	return (new_tree);
}

int	get_depth(unsigned int idx)
{
	int	pow;

	pow = 1;
	while (1)
	{
		if (idx < ft_pow(2, pow))
			break ;
		pow++;
	}
	return (pow);
}

int	*get_path(int idx)
{
	int	i;
	int	num;
	int	pow;
	int	depth;
	int	*res;

	num = 1;
	pow = 0;
	depth = get_depth((unsigned int)idx);
	res = (int *)malloc(sizeof(int) * (depth));
	i = depth - 1;
	while (num > 0 && i > 0)
	{
		num = idx / ft_pow(2, pow++);
		res[--i] = num % 2;
	}
	res[depth - 1] = -1;
	return (res);
}

void	add_tree(t_tree **tree, int idx, t_tree *newtree, int i)
{
	int		*path;
	t_tree	*temp;

	if (*tree == NULL || idx == 1)
	{
		*tree = newtree;
		return ;
	}
	if (newtree == NULL)
		return ;
	temp = *tree;
	path = get_path(idx);
	while (path[++i + 1] != -1)
	{
		if (path[i] == 0)
			temp = temp->left;
		else if (path[i] == 1)
			temp = temp->right;
	}
	if (path[i] == 0)
		temp->left = newtree;
	else if (path[i] == 1)
		temp->right = newtree;
	safety_free((void **)&path);
}
