/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:56:44 by natallia          #+#    #+#             */
/*   Updated: 2025/04/09 20:27:45 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell_phase	mshell_parser(t_mshell *mshell)
{
	int	status;

	status = PARSER_DEFAULT;
	parse_variables(&(mshell->tokens), mshell->vars, &status);
	if (!mshell->tokens)
		return (MINISHELL_READLINE);
	if (status == PARSER_CRITICAL_ERROR)
		return (ft_putendl_fd(ERR_MEM, 2), MINISHELL_CLEANUP);
	parse_wildcards(&(mshell->tokens), &status);
	if (status == PARSER_CRITICAL_ERROR)
		return (ft_putendl_fd(ERR_MEM, 2), MINISHELL_CLEANUP);
	mshell->ast = build_ast(mshell->tokens, NULL, &status);
	free_tokens(&mshell->tokens);
	if (status == PARSER_ERROR)
	{
		mshell->vars.exit_status = 2;
		return (free_ast(&mshell->ast), MINISHELL_READLINE);
	}
	if (status == PARSER_CRITICAL_ERROR)
	{
		mshell->vars.exit_status = 1;
		return (ft_putendl_fd(ERR_MEM, 2), MINISHELL_CLEANUP);
	}
	return (MINISHELL_EXECUTER);
}
