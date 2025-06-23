/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:16:05 by natallia          #+#    #+#             */
/*   Updated: 2025/04/11 12:12:52 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell_phase	mshell_lexer(t_mshell *mshell)
{
	int	status;

	status = LEXER_DEFAULT;
	status = generate_tokens(mshell->input, &mshell->tokens);
	free(mshell->input);
	mshell->input = NULL;
	if (incomplete_command_line(mshell->tokens))
		return (MINISHELL_READMORE);
	if (status == LEXER_ERROR)
	{
		mshell->vars.exit_status = 2;
		free_tokens(&mshell->tokens);
		return (MINISHELL_READLINE);
	}
	if (status == LEXER_CRITICAL_ERROR)
	{
		mshell->vars.exit_status = 1;
		return (ft_putendl_fd(ERR_MEM, 2), MINISHELL_CLEANUP);
	}
	return (MINISHELL_PARSER);
}
