# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: natallia <natallia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 13:03:26 by nkhamich          #+#    #+#              #
#    Updated: 2025/04/13 20:18:21 by natallia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iincludes -I$(LIBFT_PATH) -g

SRC_ENVP	= envp/utils.c envp/variables.c envp/quoted_string.c envp/wildcards.c

SRC_EXEC	= execution/ft_builtin_pwd.c execution/ft_builtin_env.c execution/ft_builtin_echo.c \
				execution/ft_execution.c execution/exec_utils.c execution/common_utils.c \
				execution/env_utils.c execution/ft_builtin_cd.c execution/ft_builtin_export.c \
				execution/ft_builtin_export_utils.c execution/ft_builtin_unset.c execution/exec_init_clean.c \
				execution/ft_exec_pipe.c execution/ft_builtin_exit.c execution/ft_redirection.c \
				execution/ft_redirection_heredoc.c execution/ft_redirection_group.c execution/signals.c \
				execution/ft_execution_groups.c execution/ft_execve_cmd.c execution/signals_2.c \
				execution/ft_redirection_heredoc_utils.c execution/check_var.c

SRC_LEXER	= lexer/and.c lexer/parentheses.c lexer/pipe_or.c lexer/quote.c lexer/redirection.c \
				lexer/semicolon.c lexer/generate_tokens.c lexer/variable.c lexer/whitespace.c lexer/word.c \
				lexer/utils.c

SRC_MAIN	= mshell_cleanup.c mshell_execution.c mshell_lexer.c mshell_main.c mshell_parser.c \
				mshell_readline.c mshell_readmore.c mshell_start.c

SRC_PARSER	= parser/argument.c parser/assignment.c parser/ast_cleanup.c \
				parser/ast_utils.c parser/ast_build.c parser/command.c parser/group.c \
				parser/parentheses.c parser/ast_print.c parser/redirection.c

SRC_TOKENS	= tokens/token_cleanup.c tokens/token_create.c tokens/token_operations.c tokens/print_tokens.c \
				tokens/utils.c

SRC			= $(SRC_ENVP) $(SRC_EXEC) $(SRC_LEXER) $(SRC_MAIN) $(SRC_PARSER) $(SRC_TOKENS)

OBJ_DIR		= obj
OBJ			= $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS	= $(SRC_BONUS:%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBS = -lreadline

UNAME_S		:= $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	CFLAGS	+= -I/usr/local/opt/readline/include
	LDFLAGS	+= -L/usr/local/opt/readline/lib
endif

all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "Object directory created for $(NAME)."

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "$(NAME) executable created successfully."

$(LIBFT):
	@make -C $(LIBFT_PATH) all

bonus: all

clean:
	@make -C $(LIBFT_PATH) clean
	@rm -rf $(OBJ_DIR)
	@echo "Object files cleaned for $(NAME)."

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -rf $(NAME)
	@echo "Executable fully cleaned."

re: fclean all

.PHONY: all bonus clean fclean re libft
