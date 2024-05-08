/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:29:35 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 15:56:34 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_logical(t_tree *t, int fd[])
{
	if (is_garbage_node(t->left))
		visit(t->left, fd);
	if (is_garbage_node(t->right))
	{
		back_up_stdfd(&fd[0], &fd[1], &fd[2], 2);
		g_mini.tmp_count++;
		if (g_mini.exit_code == 0 && t->key == AND)
			visit(t->right, fd);
		else if (g_mini.exit_code != 0 && t->key == OR)
			visit(t->right, fd);
	}
}

int	is_garbage_node(t_tree *t)
{
	if (t)
	{
		if (t->key == AND || t->key == OR || \
			t->key == STD_IN || t->key == STD_OUTT || \
			t->key == HEREDOC || t->key == STD_OUTA || \
			t->key == PIPE || t->key == COMMAND)
		{
			if (t->value[0] != '\0')
				return (1);
		}
	}
	return (0);
}

void	unlink_files(int num)
{
	int		i;
	char	*filename;

	if (num == 1)
	{
		filename = get_heredoc_filename(g_mini.tmp_count);
		if (access(filename, F_OK) == 0)
			unlink_tmp_in_here_doc(filename);
	}
	else if (num == 2)
	{
		i = 0;
		while (i++ < g_mini.tmp_count)
		{
			filename = get_heredoc_filename(i);
			if (access(filename, F_OK) == 0)
				unlink_tmp_in_here_doc(filename);
		}
	}
}

void	unlink_command(char *value, int num, char **buf)
{
	char	**split;

	if (g_mini.is_unlink == 1)
	{
		split = ft_split_token(value, ' ');
		if (num == 1 && (ft_memcmp(split[0], "ls", 3) == 0))
		{
			g_mini.is_unlink = 0;
			unlink_files(num);
		}
		if (num == 2)
		{
			g_mini.is_unlink = 0;
			unlink_files(num);
		}
		safety_dimention_free(split);
	}
	if (num == 2)
	{
		g_mini.continue_flag = 0;
		free_mini();
		safety_free((void **)buf);
	}
}

void	visit(t_tree *t, int fd[])
{
	if (!t)
		return ;
	if (t->key == AND || t->key == OR)
		do_logical(t, fd);
	else if (t->key == PIPE)
		do_pipe(t, fd);
	else if (t->key == STD_IN || t->key == STD_OUTT || \
			t->key == HEREDOC || t->key == STD_OUTA)
	{
		if (t->key == STD_IN && is_garbage_node(t->right) && \
			t->right->key == HEREDOC)
			exception_redirection(&t);
		else
			do_redirection(t);
		if (!g_mini.exit_code && is_garbage_node(t->right))
			visit(t->right, fd);
	}
	else if (t->key == COMMAND)
	{
		unlink_command(t->value, 1, NULL);
		do_command(t->value);
	}
}
