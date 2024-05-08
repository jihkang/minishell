/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:34:42 by pjang             #+#    #+#             */
/*   Updated: 2023/01/05 14:40:23 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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
