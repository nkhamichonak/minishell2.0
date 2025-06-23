/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:41:57 by natallia          #+#    #+#             */
/*   Updated: 2025/04/13 12:12:33 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokens.h"
# include <stdbool.h>

# define PARSER_DEFAULT 0
# define PARSER_ERROR 1
# define PARSER_CRITICAL_ERROR 2

typedef enum e_node_type
{
	NODE_SEQUENCE,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_GROUP,
	NODE_COMMAND
}	t_node_type;

typedef struct s_redirect
{
	char				*filename;
	t_token_type		redir_type;
	bool				quoted;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command
{
	char			*cmd_name;
	char			**args;
	t_list			*temp_assignments;
	t_list			*perm_assignments;
	t_redirect		*redirects;
}	t_command;

typedef struct s_ast_node
{
	t_node_type			type;
	t_command			*cmd;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_redirect			*group_redirs;
	struct s_ast_node	*subtree;
}	t_ast_node;

// general AST-building toolkit
t_ast_node	*build_ast(t_token *start, t_token *end, int *status);
t_token		*get_separator(t_token *token, t_token *last);
t_token		*get_main_operator(t_token *token, t_token *last);
t_ast_node	*create_ast_node(t_node_type type);
t_node_type	get_node_type(t_token_type token_type);
void		print_ast(t_ast_node *node, int level);
void		free_ast(t_ast_node **node);
void		free_ast_node(t_ast_node **node);

// command-level parsing and utils
t_ast_node	*process_command(t_token *token, t_token *last, int *status);
bool		is_valid_assignment(t_token *token);
int			add_assignment(t_ast_node *node, t_token **token, t_token *end);
bool		is_valid_redirection(t_token *token, int *status);
int			add_cmd_redir(t_ast_node *node, t_token **token, t_token *end);
int			add_argument(t_command *cmd, t_token **token, t_token *end);
void		free_args(char ***args);

// parentheses group-level parsing and utils
bool		contains_group(t_token *token, t_token *last);
t_ast_node	*process_group(t_token *start, t_token *end, int *status);
t_token		*skip_open_paren(t_token *token, t_token *last);
t_token		*get_close_paren(t_token *token, t_token *last);
int			add_grp_redir(t_ast_node *node, t_token **token, t_token *end);

#endif
