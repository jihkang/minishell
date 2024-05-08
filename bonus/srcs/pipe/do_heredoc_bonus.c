/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:49:08 by pjang             #+#    #+#             */
/*   Updated: 2022/12/27 16:49:49 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

char	*get_heredoc_filename(int tmp_count)
{
	char	*res;
	t_list	*temp;

	res = NULL;
	temp = g_mini.heredoc;
	while (temp && --tmp_count > 0)
		temp = temp->next;
	res = (char *)temp->content;
	return (res);
}

void	logical_heredoc(void)
{
	char	*num;
	char	*temp;

	g_mini.tmp_count++;
	num = ft_itoa(g_mini.tmp_count);
	temp = ft_strjoin("tmp.heredoc", num);
	safety_free((void **)&num);
	ft_lstadd_back(&g_mini.heredoc, ft_lstnew((void *)temp));
}

void	do_heredoc(t_tree *t, int fd[])
{
	char	*limiter;

	if (t->key == HEREDOC)
	{
		limiter = get_redirection_token(t, 2);
		if (g_mini.continue_flag)
		{
			safety_free((void **)&limiter);
			return ;
		}
		here_doc(limiter);
		safety_free((void **)&limiter);
	}
	if (is_garbage_node(t->left))
		do_heredoc(t->left, fd);
	if (t->key == AND || t-> key == OR)
		logical_heredoc();
	if (is_garbage_node(t->right))
		do_heredoc(t->right, fd);
}
