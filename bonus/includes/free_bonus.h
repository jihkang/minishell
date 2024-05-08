/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:53:45 by pjang             #+#    #+#             */
/*   Updated: 2022/12/27 15:24:38 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_BONUS_H
# define FREE_BONUS_H

# include "global_bonus.h"
# include "env_bonus.h"

void	free_env(t_env *env);
void	free_node(t_list **cur);
void	clear_envlst(t_list **lst);

#endif
