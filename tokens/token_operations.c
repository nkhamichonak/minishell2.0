/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:31:33 by natallia          #+#    #+#             */
/*   Updated: 2025/04/13 12:19:50 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

char	*concatenate_tokens(t_token **token, t_token *end, bool *quoted)
{
	char	*result;
	char	*temp;

	result = ft_strdup("");
	if (result == NULL)
		return (NULL);
	while (*token && *token != end
		&& ((*token)->type == WORD
			|| (*token)->type == STR_DOUBLE_Q
			|| (*token)->type == STR_SINGLE_Q
			|| (*token)->type == VARIABLE))
	{
		temp = ft_strjoin_free(result, (*token)->value);
		if (temp == NULL)
			return (NULL);
		result = temp;
		if ((*token)->type == STR_DOUBLE_Q || (*token)->type == STR_SINGLE_Q)
			*quoted = true;
		*token = (*token)->next;
	}
	return (result);
}

void	insert_sublist(t_token **head, t_token *temp, t_token *sublst)
{
	t_token	*prev;
	t_token	*next;
	t_token	*last;

	if (!*head || !temp || !sublst)
		return ;
	prev = NULL;
	next = temp->next;
	if (*head != temp)
	{
		prev = *head;
		while (prev && prev->next != temp)
			prev = prev->next;
	}
	last = sublst;
	while (last->next)
		last = last->next;
	last->next = next;
	if (prev)
		prev->next = sublst;
	else
		*head = sublst;
	free(temp->value);
	free(temp);
}

t_token	*get_last_token(t_token *token_lst)
{
	while (token_lst != NULL && token_lst->next != NULL)
		token_lst = token_lst->next;
	return (token_lst);
}

t_token	*get_previous_token(t_token *head, t_token *target)
{
	t_token	*prev;

	prev = NULL;
	while (head && head != target)
	{
		prev = head;
		head = head->next;
	}
	return (prev);
}
