/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:16:39 by nkhamich          #+#    #+#             */
/*   Updated: 2025/04/13 12:18:04 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**reallocate_args(t_command *cmd, char *arg, int count)
{
	char	**new_args;
	int		i;

	new_args = malloc((count + 2) * sizeof(char *));
	if (new_args == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_args[i] = ft_strdup(cmd->args[i]);
		if (new_args[i] == NULL)
		{
			free_args(&new_args);
			return (NULL);
		}
		i++;
	}
	new_args[i] = ft_strdup(arg);
	if (new_args[i] == NULL)
	{
		free_args(&new_args);
		return (NULL);
	}
	new_args[i + 1] = NULL;
	return (new_args);
}

int	add_argument(t_command *cmd, t_token **token, t_token *end)
{
	int		count;
	char	**new_args;
	char	*concatenated_arg;
	bool	quoted;

	quoted = false;
	concatenated_arg = concatenate_tokens(token, end, &quoted);
	if (concatenated_arg == NULL)
		return (PARSER_CRITICAL_ERROR);
	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	new_args = reallocate_args(cmd, concatenated_arg, count);
	free(concatenated_arg);
	if (new_args == NULL)
		return (PARSER_CRITICAL_ERROR);
	free_args(&(cmd->args));
	cmd->args = new_args;
	return (PARSER_DEFAULT);
}
