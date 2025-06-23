/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:37:23 by natallia          #+#    #+#             */
/*   Updated: 2025/04/13 20:19:52 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "envp.h"
# include "execution.h"
# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ERR_MEM "minishell: memory allocation failed"
# define ERR_EOF "minishell: syntax error: unexpected end of file"

typedef enum e_mshell_phase
{
	MINISHELL_READLINE,
	MINISHELL_READMORE,
	MINISHELL_LEXER,
	MINISHELL_PARSER,
	MINISHELL_EXECUTER,
	MINISHELL_CLEANUP,
	MINISHELL_EXIT
}	t_mshell_phase;

typedef struct s_mshell
{
	char		*input;
	t_vars		vars;
	t_token		*tokens;
	t_ast_node	*ast;
	t_executer	exec;
	char		*prompt;
}	t_mshell;

t_mshell_phase	mshell_start(t_mshell *mshell, char **envp);
t_mshell_phase	mshell_readline(t_mshell *mshell);
t_mshell_phase	mshell_readmore(t_mshell *mshell);
t_mshell_phase	mshell_lexer(t_mshell *mshell);
t_mshell_phase	mshell_parser(t_mshell *mshell);
t_mshell_phase	mshell_cleanup(t_mshell *mshell);
t_mshell_phase	mshell_execution(t_mshell *mshell);

#endif
