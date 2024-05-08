/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:32:58 by gangjiho          #+#    #+#             */
/*   Updated: 2022/12/27 15:24:19 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_BONUS_H
# define GLOBAL_BONUS_H
# include "env_bonus.h"
# include "../libft/libft.h"

typedef struct s_prs
{
	int		s_e[2];
	char	*priority;
	t_list	*quote;
	t_list	*pts;
	t_list	*logical;
	t_list	*pipe;
	t_list	*redirect;
}				t_prs;

typedef struct s_tkn
{
	int		idx;
	char	*value;
}				t_tkn;

typedef struct s_tree
{
	int				key;
	char			*value;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;

typedef struct s_mini
{
	t_list	*env;
	t_tkn	*tkn;
	t_list	*token;
	t_tree	*tree;
	t_list	*heredoc;
	int		tmp_count;
	int		fd[2];
	int		continue_flag;
	int		pts_flag;
	int		pts_exist;
	int		is_child;
	int		is_minishell;
	int		is_heredoc;
	int		is_unlink;
	int		exit_code;
	int		*tree_idx;
	void	*contents;
}				t_mini;

t_mini	g_mini;

#endif
