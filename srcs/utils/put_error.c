/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:40:59 by pjang             #+#    #+#             */
/*   Updated: 2022/12/04 21:57:26 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	put_error(char *error_msg, char *token)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error_msg, 2);
	exit(EXIT_FAILURE);
}
