/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:08:52 by pjang             #+#    #+#             */
/*   Updated: 2022/12/27 16:37:17 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

char	**get_error_token(void)
{
	char	**res;

	res = (char **)malloc(sizeof(char *) * 14);
	if (!res)
	{
		put_error2(strerror(errno), "malloc");
		return (NULL);
	}
	res[0] = ft_strdup("<");
	res[1] = ft_strdup("<<");
	res[2] = ft_strdup(">");
	res[3] = ft_strdup(">>");
	res[4] = ft_strdup("|");
	res[5] = ft_strdup("&");
	res[6] = ft_strdup(";");
	res[7] = ft_strdup("(");
	res[8] = ft_strdup(")");
	res[9] = ft_strdup("\0");
	res[10] = ft_strdup("#");
	res[11] = ft_strdup("`");
	res[12] = ft_strdup("*");
	res[13] = NULL;
	return (res);
}

int	fp(char *token, int i)
{
	if (0 <= i && i <= 8)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token \'", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd("\'\n", 2);
	}
	else if (i == 9 || i == 10)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
		ft_putstr_fd(" \'new line\'\n", 2);
	}
	else if (i > 10)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
	if (0 <= i && i <= 10)
		g_mini.exit_code = 258;
	else if (10 < i)
		g_mini.exit_code = 1;
	else if (0 > i)
		g_mini.exit_code = 0;
	return (g_mini.exit_code);
}

int	middle_fp(char *token, int i, char ***e_token)
{
	int	res;

	safety_dimention_free(*e_token);
	res = fp(token, i);
	if (res)
		g_mini.continue_flag = 1;
	return (res);
}

int	valid_token(char *token, int idx)
{
	int		i;
	char	**e_token;

	if (!token)
		token = ft_strdup("");
	e_token = get_error_token();
	i = -1;
	while (e_token[++i] != NULL)
	{
		if (ft_strncmp(token, e_token[i], 2) == 0)
		{
			if (0 <= i && i <= 10)
				return (middle_fp(token, i, &e_token));
			else if (10 < i)
			{
				if (idx != HEREDOC)
					return (middle_fp(token, i, &e_token));
				else
					break ;
			}
		}
	}
	safety_dimention_free(e_token);
	return (0);
}
