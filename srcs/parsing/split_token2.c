/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:34:25 by pjang             #+#    #+#             */
/*   Updated: 2023/01/05 13:31:14 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_strs_token(const char *s, char c)
{
	int	i;
	int	flag;
	int	result;

	i = 0;
	flag = 0;
	result = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]) == c)
			i++;
		if (s[i] != '\0')
			result++;
		while (s[i] && (ft_isspace(s[i]) != c || flag))
		{
			if (!devide_command2((char *)(s + i), &flag, &i))
				break ;
			i++;
			get_flag_match(&flag, s[i], NULL, &i);
		}
	}
	return (result);
}
