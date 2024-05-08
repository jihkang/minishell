/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 21:21:33 by pjang             #+#    #+#             */
/*   Updated: 2022/12/27 16:49:37 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_redirection_token(t_tree *t, int num)
{
	char	**split;
	char	*redirection_token;

	split = NULL;
	redirection_token = NULL;
	if (num == 1)
		split = ft_split_token(t->right->value, ' ');
	else if (num == 2)
		split = ft_split_token(t->value, ' ');
	if (split[1] && ft_memcmp(split[1], "\"\"", 3) == 0)
		redirection_token = ft_strdup(split[1]);
	else if (split[1])
		redirection_token = ft_strdup_flag(split[1]);
	if (!redirection_token)
		redirection_token = ft_strdup("");
	safety_dimention_free(split);
	if (num == 1 && valid_token(redirection_token, t->right->key))
		return (redirection_token);
	if (num == 2 && valid_token(redirection_token, t->key))
		return (redirection_token);
	return (redirection_token);
}

void	do_redirection(t_tree *t)
{
	char	*filename;
	char	*redirection_token;

	redirection_token = get_redirection_token(t, 2);
	if (g_mini.continue_flag)
	{
		safety_free((void **)&redirection_token);
		return ;
	}
	filename = get_heredoc_filename(g_mini.tmp_count);
	if (t->key == STD_IN || t->key == HEREDOC)
	{
		if (t->key == STD_IN)
			input_redirection(redirection_token);
		if (t->key == HEREDOC)
			input_redirection(filename);
	}
	if (t->key == STD_OUTT || t->key == STD_OUTA)
	{
		if (t->key == STD_OUTT)
			output_redirection(redirection_token);
		if (t->key == STD_OUTA)
			append_redirection(redirection_token);
	}
	safety_free((void **)&redirection_token);
}

void	exception_redirection(t_tree **t)
{
	int		fd;
	char	*redirection_token;
	t_tree	*tree;

	tree = *t;
	redirection_token = get_heredoc_filename(g_mini.tmp_count);
	input_redirection(redirection_token);
	redirection_token = get_redirection_token(tree, 2);
	fd = open(redirection_token, O_RDONLY, 0644);
	if (fd == -1)
		put_error2(strerror(errno), redirection_token);
	else if (close(fd) == -1)
		put_error2(strerror(errno), redirection_token);
	safety_free((void **)&redirection_token);
	*t = tree->right;
}
