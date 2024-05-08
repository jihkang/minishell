/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:53:26 by pjang             #+#    #+#             */
/*   Updated: 2022/12/27 15:18:57 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BULTIN_BONUS_H
# define BULTIN_BONUS_H

# include "list_bonus.h"
# include "env_bonus.h"
# include <dirent.h>

void	ft_export(char *str);
void	ft_unset(char *str);
void	ft_cd(char *path);
char	*ft_pwd(void);
char	*ft_pwd2(void);
void	ft_exit(char *err);
void	ft_echo(char **split, int flag);

int		ft_access(char *path);
char	*ft_astric(char *path);
int		is_in_quote(char *cmd);
int		ft_match(char *str, char *ptn);
int		ft_strrchr2(char *str, char c);
char	*get_path2(char *str, int r);
char	*get_file(char *str);
char	*ft_astric_sub(char *o_path, char *o_name);

#endif
