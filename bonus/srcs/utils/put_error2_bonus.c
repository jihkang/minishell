/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:40:59 by pjang             #+#    #+#             */
/*   Updated: 2022/12/27 15:56:03 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	put_error2(char *error_msg, char *token)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error_msg, 2);
	g_mini.exit_code = 1;
	return (1);
}
