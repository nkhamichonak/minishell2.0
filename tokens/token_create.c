/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:46:02 by nkhamich          #+#    #+#             */
/*   Updated: 2025/04/07 12:46:49 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

t_token	*create_token(t_token_type type, const char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->value = NULL;
	new->next = NULL;
	if (value == NULL)
		return (new);
	new->value = ft_strdup(value);
	if (new->value == NULL)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

void	append_token(t_token **token_lst, t_token *new)
{
	t_token	*last;

	last = NULL;
	if (*token_lst == NULL)
		*token_lst = new;
	else
	{
		last = get_last_token(*token_lst);
		last->next = new;
	}
}
