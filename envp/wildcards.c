/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:43:55 by nkhamich          #+#    #+#             */
/*   Updated: 2025/04/10 11:42:37 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

static bool	match_pattern(const char *pattern, const char *filename)
{
	if (*pattern == '\0' && *filename == '\0')
		return (true);
	if (*pattern == '*')
	{
		while (*filename != '\0')
		{
			if (match_pattern(pattern + 1, filename))
				return (true);
			filename++;
		}
		return (match_pattern(pattern + 1, filename));
	}
	if (*pattern == *filename)
		return (match_pattern(pattern + 1, filename + 1));
	return (false);
}

static bool	add_match_to_file_lst(char *name, t_token **files_lst, bool *first)
{
	t_token		*file_token;
	t_token		*space_token;

	file_token = create_token(WORD, name);
	if (file_token == NULL || file_token->value == NULL)
	{
		free_tokens(files_lst);
		return (false);
	}
	if (*first == false)
	{
		space_token = create_token(SPACE, " ");
		if (space_token == NULL || space_token->value == NULL)
		{
			free_one_token(&file_token);
			free_tokens(files_lst);
			return (false);
		}
		append_token(files_lst, space_token);
	}
	append_token(files_lst, file_token);
	*first = false;
	return (true);
}

static t_token	*get_matching_files(const char *pattern)
{
	DIR				*current_dir;
	struct dirent	*entry;
	t_token			*files_lst;
	bool			first;

	files_lst = NULL;
	first = true;
	current_dir = opendir(".");
	if (current_dir == NULL)
		return (NULL);
	entry = readdir(current_dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && match_pattern(pattern, entry->d_name))
		{
			if (!add_match_to_file_lst(entry->d_name, &files_lst, &first))
			{
				closedir(current_dir);
				return ((t_token *) -1);
			}
		}
		entry = readdir(current_dir);
	}
	closedir(current_dir);
	return (files_lst);
}

static bool	qualifies_for_globbing(t_token *prev, t_token *token)
{
	t_token	*next;
	bool	prev_is_quoted;
	bool	next_is_quoted;
	bool	self_is_unquoted;

	next = token->next;
	prev_is_quoted = prev && ((prev->type == STR_DOUBLE_Q && prev->value[0])
			|| (prev->type == STR_SINGLE_Q && prev->value[0]));
	next_is_quoted = next && ((next->type == STR_DOUBLE_Q && next->value[0])
			|| (next->type == STR_SINGLE_Q && next->value[0]));
	self_is_unquoted = token->type == WORD && ft_strchr(token->value, '*');
	if (!prev_is_quoted && !next_is_quoted && self_is_unquoted)
		return (true);
	return (false);
}

void	parse_wildcards(t_token **tokens, int *status)
{
	t_token	*temp;
	t_token	*prev;
	t_token	*files_lst;

	prev = NULL;
	temp = *tokens;
	while (temp)
	{
		if (qualifies_for_globbing(prev, temp))
		{
			files_lst = get_matching_files(temp->value);
			if (files_lst == (t_token *) -1)
			{
				*status = ENVP_CRITICAL_ERROR;
				return ;
			}
			if (files_lst)
			{
				insert_sublist(tokens, temp, files_lst);
				update_temp(&temp, prev, tokens);
			}
		}
		prev = temp;
		temp = temp->next;
	}
}
