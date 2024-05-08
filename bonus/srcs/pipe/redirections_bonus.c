/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:22:57 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 16:06:06 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	input_redirection(char *infile)
{
	int		fdin;
	char	*input;

	input = ft_strdup_flag(infile);
	fdin = open(input, O_RDONLY, 0644);
	free(input);
	if (fdin == -1)
		return (put_error2(strerror(errno), "infile"));
	if (dup2(fdin, STDIN_FILENO) == -1)
		return (put_error2(strerror(errno), "dup2 infile"));
	if (close(fdin) == -1)
		return (put_error2(strerror(errno), "close infile"));
	g_mini.exit_code = 0;
	return (0);
}

int	output_redirection(char *outfile)
{
	int		fdout;
	char	*output;

	output = ft_strdup_flag(outfile);
	fdout = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(output);
	if (fdout == -1)
		return (put_error2(strerror(errno), "outfile"));
	if (dup2(fdout, STDOUT_FILENO) == -1)
		return (put_error2(strerror(errno), "dup2 outfile"));
	if (close(fdout) == -1)
		return (put_error2(strerror(errno), "close outfile"));
	g_mini.exit_code = 0;
	return (0);
}

int	append_redirection(char *outfile)
{
	int		fdout;
	char	*output;

	output = ft_strdup_flag(outfile);
	fdout = open(output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(output);
	if (fdout == -1)
		return (put_error2(strerror(errno), "outfile"));
	if (dup2(fdout, STDOUT_FILENO) == -1)
		return (put_error2(strerror(errno), "dup2 outfile"));
	if (close(fdout) == -1)
		return (put_error2(strerror(errno), "close outfile"));
	g_mini.exit_code = 0;
	return (0);
}
