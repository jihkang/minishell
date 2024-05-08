/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:35:19 by pjang             #+#    #+#             */
/*   Updated: 2023/01/05 13:50:20 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "global.h"
# include "bultin.h"
# include "env.h"
# include "free.h"
# include "list.h"
# include <termios.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# define START (0)
# define END (1)
# define READ (0)
# define WRITE (1)
# define COMMAND (43)		// upper C
# define B_QUOTE (34)		// "
# define S_QUOTE (39)		// '
# define AND (38)			// &&
# define OR (125)			// ||
# define PIPE (124)			// |
# define OPEN_PTS (40)		// ( - parenthesis
# define CLOSE_PTS (41)		// )
# define REDIR (59)		// redirection
# define STD_IN (60)		// <
# define HEREDOC (61)		// <<
# define STD_OUTT (62)		// >
# define STD_OUTA (63)		// >>

// init
void		init_prs(t_prs *prs);
void		init_tkn(t_list *temp);
void		init_mini(void);

// utils
void		into_env(char **envp);
int			ft_strcmp(char *str, char *str2);
int			ft_strichr(char *str, char c);
int			ft_max(int a, int b);
u_int64_t	ft_pow(u_int64_t num, u_int64_t power);
void		free_prs(t_prs *prs);
void		free_tkn(void *tkn);
void		free_mini(void);
void		safety_free(void **str);
void		safety_dimention_free(char **strs);
void		put_error(char *error_msg, char *token);
int			put_error2(char *error_msg, char *token);
void		put_error3(char *error_msg, char *token);
void		swap_list(int a, int b);
void		ft_swap_p_char(char **a, char **b);

// token
void		free_tkn2(void *tkn);
void		clear_tkn(t_tkn **tkn, void (*del)(void *));
void		set_token(t_tkn *token, int idx, char *value);
int			set_logical_pipe_token(char *buf, int i);
int			set_redirection_token(t_list *temp, char *buf, int i);
void		set_command_token(t_list **temp, char *buf, int *i);
char		*get_token_value(t_list *temp, char *buf, int i);
void		get_token_array(t_prs *prs);
void		get_token_list(void);
void		swap_token(int *sort_idx);
void		right_arrange_token(int i);
int			*sort_redirection_idx(void);

int			devide_command(char *c, char **str, int *flag, int *i);
int			devide_command2(char *c, int *flag, int *i);
char		**ft_split_token(const char *s, char c);
void		get_flag_match(int *flag, char c, char **str, int *i);
int			get_strs_token(const char *s, char c);

// tree
int			is_ptscount(char *str, int i);
int			is_garbage_node(t_tree *t);
void		clear_tree(t_tree **t, void (*del)(void **));
void		in_tree(t_prs *prs);
int			*get_tree_idx(t_prs *prs);
t_tree		*new_tree(int key, char *value);
int			get_depth(unsigned int idx);
int			*get_path(int idx);
void		add_tree(t_tree **tree, int idx, t_tree *newtree, int i);

// parsing department
int			is_seq(char *c);
int			is_seq1(char *c);
int			is_seq2(char *c);
int			is_seq3(char *c);

// parsing divide
void		change_env(void);
int			get_count_dalar(t_tkn *tkn);
t_env		*get_env_value(t_list *list, t_tkn *tkn, int start, int i);
char		*get_new_value(t_env **env, t_tkn *tkn, int i);
void		change_to_value(t_list **list, int i);
int			is_quote(char *str);
void		divide_quote(char *buf, t_prs *prs);
void		divide_pts(t_prs *prs);
void		divide_logical(t_prs *prs);
void		divide_pipe(t_prs *prs);
void		divide_redirection(t_prs *prs);

// parsing etc
int			ft_isspace(char c);
int			valid_token_list(t_prs *prs);
void		parsing(char *buf, int fd[]);
void		do_priority(char *buf, t_prs *prs);
char		*get_content(char	*buf, t_prs *prs);
void		into_list(char *buf, t_prs *prs, int no);
void		back_up_stdfd(int *fd_in, int *fd_out, int *fd_err, int n);
void		run_cmd(char *buf);
int			is_builtin(char	*token);
int			get_max_redirection_count(void);
int			get_max_command_count(void);
void		visit(t_tree *t, int fd[]);
int			is_garbage_node(t_tree *t);
int			input_we_valid(char *buf);
int			get_result_valid_we(int *count);
void		valid_we(int *flag, char c, int **count);
int			input_bash_valid(char *buf);
char		*change_env_exit_code(t_tkn *tkn, int i);

// pipe
void		do_pipe(t_tree *t, int fd[]);
char		*get_heredoc_filename(int tmp_count);
void		do_heredoc(t_tree *t, int fd[]);
char		*get_redirection_token(t_tree *t, int num);
void		do_redirection(t_tree *t);
void		exception_redirection(t_tree **t);
int			valid_token(char *token, int idx);
int			input_redirection(char *infile);
int			output_redirection(char *outfile);
int			append_redirection(char *outfile);
int			here_doc(char *limiter);
void		unlink_tmp_in_here_doc(char *filename);

// exec
int			is_builtin2(char	*cmd);
void		exec_builtin(char	**cmd);
void		exec_cmd(char	**cmd);
void		unlink_command(char *value, int num, char **buf);
void		do_command(char	*tok);
int			is_asterisk(char **cmd);
void		exec_asterisk(char	**cmd, int idx);
char		*real_path(char	**cmd);
char		**ft_split_flag(char *str, char c);
char		*ft_strdup_flag(char *str);

// signal
void		set_signal(void);

#endif