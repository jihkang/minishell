/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_we_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:21:50 by pjang             #+#    #+#             */
/*   Updated: 2023/01/05 13:44:10 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	put_valid_we_error(int n)
{
	ft_putstr_fd("minishell: syntax error: unexpected token '", 2);
	if (n == 1)
		ft_putstr_fd("\''\n", 2);
	if (n == 2)
		ft_putstr_fd("\"'\n", 2);
	if (n == 3)
		ft_putstr_fd("`'\n", 2);
	if (n == 4)
		ft_putstr_fd(")'\n", 2);
	if (n == 5)
		ft_putstr_fd("('\n", 2);
	return (0);
}

int	is_quote_valid(char *buf)
{
	int	res;
	int	flag;
	int	*count;

	res = 0;
	flag = 0;
	count = (int *)malloc(sizeof(int) * 3);
	count[0] = 0;
	count[1] = 0;
	count[2] = 0;
	while (*buf)
	{
		valid_we(&flag, *buf, &count);
		buf++;
	}
	res = get_result_valid_we(count);
	safety_free((void **)&count);
	return (res);
}

void	set_pts_exist(int flag)
{
	if (!g_mini.pts_exist && flag != 0)
	{
		g_mini.pts_exist = 1;
	}
}

int	is_pts_valid(char *buf)
{
	int	flag;

	flag = 0;
	while (*buf)
	{
		set_pts_exist(flag);
		if (*buf == '(')
			flag++;
		if (*buf == ')')
			flag--;
		if (flag < 0)
			return (4);
		buf++;
	}
	if (flag < 0)
		return (4);
	if (flag > 0)
		return (5);
	return (0);
}

int	input_we_valid(char *buf)
{
	int	num;

	num = is_quote_valid(buf);
	if (num)
		return (put_valid_we_error(num));
	num = is_pts_valid(buf);
	if (num)
		return (put_valid_we_error(num));
	return (1);
}
