/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 21:47:12 by pjang             #+#    #+#             */
/*   Updated: 2022/12/27 13:30:47 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	put_error3(char *error_msg, char *token)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = ft_strjoin("minishell: ", token);
	temp2 = ft_strjoin(temp1, ": ");
	if (*token == '/')
		temp3 = ft_strjoin(temp2, error_msg);
	else
		temp3 = ft_strjoin(temp2, "command not found");
	ft_putendl_fd(temp3, 2);
	safety_free((void **)&temp1);
	safety_free((void **)&temp2);
	safety_free((void **)&temp3);
	exit(EXIT_FAILURE);
}
