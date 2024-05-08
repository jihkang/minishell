/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:53:36 by pjang             #+#    #+#             */
/*   Updated: 2022/12/27 16:25:13 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_BONUS_H
# define ENV_BONUS_H

# include "global_bonus.h"

typedef struct s_env
{
	char	*key;
	char	*value;
}				t_env;

t_env	*new_env(char *key, char *value);
char	*get_value(t_env *env);
void	init_env(char **env);
char	*get_key(t_env *env);
t_env	*make_env(char *str);
void	ft_env(void);

#endif
