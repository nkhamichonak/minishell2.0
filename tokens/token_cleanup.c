/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:08:35 by nkhamich          #+#    #+#             */
/*   Updated: 2025/04/07 12:34:59 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void	remove_token(t_token **head, t_token *target, t_token *prev)
{
	if (!head || !*head || !target)
		return ;
	if (prev)
		prev->next = target->next;
	else
		*head = target->next;
	free(target->value);
	free(target);
}

void	free_tokens(t_token **tokens)
{
	t_token		*current;
	t_token		*next;

	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

void	free_one_token(t_token **token)
{
	if (!token || !*token)
		return ;
	free((*token)->value);
	free(*token);
	*token = NULL;
}
