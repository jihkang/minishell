/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:39:13 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 17:18:16 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	if (argc != 1)
	{
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else
	{
		init_mini();
		init_env(envp);
		set_signal();
		run_cmd(NULL);
		clear_envlst(&g_mini.env);
	}
}
