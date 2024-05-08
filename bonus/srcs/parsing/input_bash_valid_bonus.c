/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bash_valid_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:31:41 by pjang             #+#    #+#             */
/*   Updated: 2023/01/05 14:39:35 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	put_error_bash_valid(char *buf, int num)
{
	ft_putstr_fd("minishell: ", 2);
	if (num <= 3)
	{
		ft_putstr_fd("syntax error near unexpected token '", 2);
		if (num == 1)
			write(2, buf, 2);
		if (num == 2)
			write(2, buf, 1);
		if (num == 3)
			ft_putstr_fd("newline", 2);
		ft_putstr_fd("'\n", 2);
	}
	if (num == 4)
		ft_putstr_fd("s^: no previous substitution\n", 2);
	return (0);
}

int	is_token_valid(char *split1, char *split2)
{
	if (split2)
		return (0);
	if (((*split1 == '&') && (*(split1 + 1) == '&')) || \
		((*split1 == '|') && (*(split1 + 1) == '|')))
		return (1);
	if (*split1 == '&' || *split1 == '|')
		return (2);
	if (*split1 == '!')
		return (3);
	if (*split1 == '^')
		return (4);
	if (*split1 == '%')
		return (5);
	return (0);
}

int	input_bash_valid(char *buf)
{
	int		num;
	char	**split;

	split = ft_split_token(buf, ' ');
	if (!split[0])
		return (0);
	num = is_token_valid(split[0], split[1]);
	if (num == 5)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(split[0], 2);
		ft_putstr_fd(": no such job\n", 2);
		safety_dimention_free(split);
		return (0);
	}
	else if (0 != num)
	{
		safety_dimention_free(split);
		return (put_error_bash_valid(buf, num));
	}
	safety_dimention_free(split);
	return (1);
}
