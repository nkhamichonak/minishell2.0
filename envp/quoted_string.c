/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:43:34 by nkhamich          #+#    #+#             */
/*   Updated: 2025/04/10 17:00:11 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

static char	*extract_variable_value(t_vars vars, char **start)
{
	size_t	var_len;
	char	*var_name;
	char	*var_value;

	(*start)++;
	var_len = 0;
	if ((*start)[var_len] == '?')
	{
		*start += 1;
		return (ft_itoa(vars.exit_status));
	}
	while (ft_isalnum((*start)[var_len]) || (*start)[var_len] == '_')
		var_len++;
	var_name = ft_substr(*start, 0, var_len);
	if (var_name == NULL)
		return (NULL);
	var_value = get_env_value(vars.global_vars, var_name);
	free(var_name);
	*start += var_len;
	return (ft_strdup(var_value));
}

static char	*expand_double_quoted_str(char *str, t_vars vars)
{
	char	*expanded_str;
	char	*var_value;
	char	temp[2];

	expanded_str = ft_strdup("");
	while (*str && expanded_str)
	{
		if (*str == '$' && (ft_isalpha(*(str + 1)) || *(str + 1) == '?'
				|| *(str + 1) == '_'))
		{
			var_value = extract_variable_value(vars, &str);
			if (var_value == NULL)
				return (free(expanded_str), NULL);
			expanded_str = ft_strjoin_free(expanded_str, var_value);
			free(var_value);
		}
		else
		{
			temp[0] = *str;
			temp[1] = '\0';
			expanded_str = ft_strjoin_free(expanded_str, temp);
			str++;
		}
	}
	return (expanded_str);
}

void	expand_quoted_str(t_token *token, t_vars vars, int *status)
{
	char	*expanded_str;

	expanded_str = expand_double_quoted_str(token->value, vars);
	if (expanded_str == NULL)
	{
		*status = ENVP_CRITICAL_ERROR;
		return ;
	}
	free(token->value);
	token->value = expanded_str;
}
