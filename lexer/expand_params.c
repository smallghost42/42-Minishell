/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:01:07 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/03 14:47:10 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	error_status(char **new_value, int i, t_sh_params *shell_params)
{
	char	*prev_error;

	prev_error = ft_itoa(shell_params->exit_status);
	*new_value = ft_strjoin(*new_value, prev_error);
	free(prev_error);
	return (i + 1);
}

static int	void_expansion(char **new_value, int i, char *str)
{
	*new_value = ft_strjoin(*new_value, str);
	return (i + 1);
}

static int	not_alpha_expansion(char *value, char **new_value, int i)
{
	char	*tmp;

	tmp = ft_strdup("$");
	tmp = join_char(tmp, value[i]);
	*new_value = ft_strjoin(*new_value, tmp);
	free(tmp);
	return (i + 1);
}

static int	quote_and_dollar(char *value, char **new_value, int i)
{
	if (value[0] == '\'' || value[0] == '\"' || (value[0] == '$' && i != 1))
		*new_value = ft_strjoin(*new_value, "$");
	return (i);
}

int	expand_params(char *value, char **new_value, int i,
		t_sh_params *shell_params)
{
	char	*tmp;
	char	*var_value;

	i++;
	if (value[i] == '\'' || value[i] == '\"')
		return (quote_and_dollar(value, new_value, i));
	else if (value[i] == '\0' || ft_isspace(value[i]))
		return (void_expansion(new_value, i - 1, "$"));
	else if (value[i] == '?')
		return (error_status(new_value, i, shell_params));
	else if (ft_strchr("$!#*@-", value[i]) || ft_isdigit(value[i]))
		return (void_expansion(new_value, i, ""));
	else if (!(ft_isalpha(value[i]) || value[i] == '_'))
		return (not_alpha_expansion(value, new_value, i));
	tmp = ft_strdup("");
	while (ft_isalpha(value[i]) || value[i] == '_' || ft_isdigit(value[i]))
	{
		tmp = join_char(tmp, value[i]);
		i++;
	}
	var_value = my_getenv(tmp, shell_params);
	*new_value = ft_strjoin(*new_value, var_value);
	free(tmp);
	return (i);
}
