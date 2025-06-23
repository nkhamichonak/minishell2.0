/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_heredoc_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:10:38 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/10 19:14:48 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_free_redirects(t_redirect *redirects)
{
	t_redirect	*temp;

	while (redirects)
	{
		temp = redirects;
		redirects = redirects->next;
		free(temp);
	}
}

char	*text_until_dollar(char *result, char *start, char *var_start)
{
	char	*temp;

	temp = ft_substr(start, 0, var_start - start);
	if (!temp)
		return (NULL);
	result = ft_strjoin_free(result, temp);
	free(temp);
	return (result);
}

char	*handle_special_var_exit(char *result, t_vars *vars)
{
	char	*exit_str;

	exit_str = ft_itoa(vars->exit_status);
	if (!exit_str)
		return (NULL);
	result = ft_strjoin_free(result, exit_str);
	free(exit_str);
	return (result);
}

char	*process_variable(char *result, char **start, \
	char *var_start, t_vars *vars)
{
	char	*var_end;
	char	*var_name;
	char	*var_value;

	if (*(var_start + 1) == '?')
	{
		result = handle_special_var_exit(result, vars);
		if (!result)
			return (NULL);
		*start = var_start + 2;
		return (result);
	}
	var_end = var_start + 1;
	while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
		var_end++;
	var_name = ft_substr(var_start + 1, 0, var_end - (var_start + 1));
	if (!var_name)
		return (NULL);
	var_value = get_env_var(vars->global_vars, var_name);
	free(var_name);
	if (var_value)
		result = ft_strjoin_free(result, var_value);
	*start = var_end;
	return (result);
}

char	*expand_variables(char *line, t_vars *vars)
{
	char	*result;
	char	*start;
	char	*var_start;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	start = line;
	while (1)
	{
		var_start = ft_strchr(start, '$');
		if (!var_start)
			break ;
		result = text_until_dollar(result, start, var_start);
		if (!result)
			return (NULL);
		result = process_variable(result, &start, var_start, vars);
		if (!result)
			return (NULL);
	}
	result = ft_strjoin_free(result, start);
	return (result);
}
