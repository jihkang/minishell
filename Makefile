# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pjang <pjang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/19 02:21:12 by pjang             #+#    #+#              #
#    Updated: 2023/01/05 14:41:35 by pjang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

READLINE_LIB = -lreadline -L${HOME}/.brew/opt/readline/lib
READLINE_INC = -I${HOME}/.brew/opt/readline/include

LIBC	=	-L ./libft/ -lft
LFT		=	libft/libft.a
SRCS	= 	./srcs/main.c \
			./srcs/builtin/cd.c \
			./srcs/builtin/echo.c \
			./srcs/builtin/env.c \
			./srcs/builtin/env_utils.c \
			./srcs/builtin/exit.c \
			./srcs/builtin/export.c \
			./srcs/builtin/free.c \
			./srcs/builtin/list.c \
			./srcs/builtin/lstutils.c \
			./srcs/builtin/pwd.c \
			./srcs/builtin/unset.c \
			./srcs/builtin/ft_access.c \
			./srcs/builtin/ft_access2.c \
			./srcs/builtin/pattern.c \
			./srcs/exec/call_astric.c \
			./srcs/exec/exec.c \
			./srcs/exec/exec2.c \
			./srcs/exec/path.c \
			./srcs/exec/ft_split_flag.c \
			./srcs/exec/ft_strdup_flag.c \
			./srcs/parsing/change_env.c \
			./srcs/parsing/change_env2.c \
			./srcs/parsing/parsing.c \
			./srcs/parsing/parsing_utils.c \
			./srcs/parsing/divide_quote.c \
			./srcs/parsing/divide_pts.c \
			./srcs/parsing/divide_logical.c \
			./srcs/parsing/divide_pipe.c \
			./srcs/parsing/divide_redirection.c \
			./srcs/parsing/is_seq.c \
			./srcs/parsing/run_cmd.c \
			./srcs/parsing/is_builtin.c \
			./srcs/parsing/token.c \
			./srcs/parsing/token2.c \
			./srcs/parsing/token3.c \
			./srcs/parsing/token4.c \
			./srcs/parsing/split_token.c \
			./srcs/parsing/split_token2.c \
			./srcs/parsing/tree.c \
			./srcs/parsing/tree2.c \
			./srcs/parsing/tree3.c \
			./srcs/parsing/in_tree.c \
			./srcs/parsing/visit.c \
			./srcs/parsing/input_we_valid.c \
			./srcs/parsing/input_we_valid2.c \
			./srcs/parsing/input_bash_valid.c \
			./srcs/pipe/do_pipe.c \
			./srcs/pipe/do_heredoc.c \
			./srcs/pipe/do_redirection.c \
			./srcs/pipe/valid.c \
			./srcs/pipe/here_doc.c \
			./srcs/pipe/redirections.c \
			./srcs/signal/signal.c \
			./srcs/utils/utils.c \
			./srcs/utils/ft_max.c \
			./srcs/utils/swap_list.c \
			./srcs/utils/init.c \
			./srcs/utils/ft_pow.c \
			./srcs/utils/put_error.c \
			./srcs/utils/put_error2.c \
			./srcs/utils/put_error3.c \
			./srcs/utils/safety_free.c \
			./srcs/utils/ft_swap_p_char.c \

B_SRCS	= 	./bonus/srcs/main_bonus.c \
			./bonus/srcs/builtin/cd_bonus.c \
			./bonus/srcs/builtin/echo_bonus.c \
			./bonus/srcs/builtin/env_bonus.c \
			./bonus/srcs/builtin/env_utils_bonus.c \
			./bonus/srcs/builtin/exit_bonus.c \
			./bonus/srcs/builtin/export_bonus.c \
			./bonus/srcs/builtin/free_bonus.c \
			./bonus/srcs/builtin/list_bonus.c \
			./bonus/srcs/builtin/lstutils_bonus.c \
			./bonus/srcs/builtin/pwd_bonus.c \
			./bonus/srcs/builtin/unset_bonus.c \
			./bonus/srcs/builtin/ft_access_bonus.c \
			./bonus/srcs/builtin/ft_access2_bonus.c \
			./bonus/srcs/builtin/pattern_bonus.c \
			./bonus/srcs/exec/call_astric_bonus.c \
			./bonus/srcs/exec/exec_bonus.c \
			./bonus/srcs/exec/exec2_bonus.c \
			./bonus/srcs/exec/path_bonus.c \
			./bonus/srcs/exec/ft_split_flag_bonus.c \
			./bonus/srcs/exec/ft_strdup_flag_bonus.c \
			./bonus/srcs/parsing/change_env_bonus.c \
			./bonus/srcs/parsing/change_env2_bonus.c \
			./bonus/srcs/parsing/parsing_bonus.c \
			./bonus/srcs/parsing/parsing_utils_bonus.c \
			./bonus/srcs/parsing/divide_quote_bonus.c \
			./bonus/srcs/parsing/divide_pts_bonus.c \
			./bonus/srcs/parsing/divide_logical_bonus.c \
			./bonus/srcs/parsing/divide_pipe_bonus.c \
			./bonus/srcs/parsing/divide_redirection_bonus.c \
			./bonus/srcs/parsing/is_seq_bonus.c \
			./bonus/srcs/parsing/run_cmd_bonus.c \
			./bonus/srcs/parsing/is_builtin_bonus.c \
			./bonus/srcs/parsing/token_bonus.c \
			./bonus/srcs/parsing/token2_bonus.c \
			./bonus/srcs/parsing/token3_bonus.c \
			./bonus/srcs/parsing/token4_bonus.c \
			./bonus/srcs/parsing/split_token_bonus.c \
			./bonus/srcs/parsing/split_token2_bonus.c \
			./bonus/srcs/parsing/tree_bonus.c \
			./bonus/srcs/parsing/tree2_bonus.c \
			./bonus/srcs/parsing/tree3_bonus.c \
			./bonus/srcs/parsing/in_tree_bonus.c \
			./bonus/srcs/parsing/visit_bonus.c \
			./bonus/srcs/parsing/input_we_valid_bonus.c \
			./bonus/srcs/parsing/input_we_valid2_bonus.c \
			./bonus/srcs/parsing/input_bash_valid_bonus.c \
			./bonus/srcs/pipe/do_pipe_bonus.c \
			./bonus/srcs/pipe/do_heredoc_bonus.c \
			./bonus/srcs/pipe/do_redirection_bonus.c \
			./bonus/srcs/pipe/valid_bonus.c \
			./bonus/srcs/pipe/here_doc_bonus.c \
			./bonus/srcs/pipe/redirections_bonus.c \
			./bonus/srcs/signal/signal_bonus.c \
			./bonus/srcs/utils/utils_bonus.c \
			./bonus/srcs/utils/ft_max_bonus.c \
			./bonus/srcs/utils/swap_list_bonus.c \
			./bonus/srcs/utils/init_bonus.c \
			./bonus/srcs/utils/ft_pow_bonus.c \
			./bonus/srcs/utils/put_error_bonus.c \
			./bonus/srcs/utils/put_error2_bonus.c \
			./bonus/srcs/utils/put_error3_bonus.c \
			./bonus/srcs/utils/safety_free_bonus.c \
			./bonus/srcs/utils/ft_swap_p_char_bonus.c \

OBJS	= $(SRCS:.c=.o)
B_OBJS	= $(B_SRCS:.c=.o)
RM		= rm -f

ifdef WITH_BONUS
OBJ_FILES = $(B_OBJS)
else
OBJ_FILES = $(OBJS)
endif

all : $(LFT) $(NAME)

$(NAME) : $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBC) $(READLINE_LIB)

$(LFT) :
	@make -s bonus -C libft
	@echo "Libft Success."

%.o : %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

bonus :
	@make WITH_BONUS=1 all

clean :
	@make -s $@ -C libft
	$(RM) $(OBJS)
	$(RM) $(B_OBJS)
	@echo "Object files removed."

fclean : clean
	@make -s $@ -C libft
	$(RM) $(NAME)
	@echo "Executable file removed."

re : fclean all

.PHONY : all bonus clean fclean re