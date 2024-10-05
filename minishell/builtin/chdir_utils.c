/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 08:54:48 by ferafano          #+#    #+#             */
/*   Updated: 2024/09/13 11:20:49 by ferafano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

void	change_to_home(char *cwd, char **copy_env)
{
	update_oldpwd("OLDPWD", cwd, copy_env);
	chdir("/home/ferafano/");
}

int	change_to_oldpwd(char *cwd, char **copy_env)
{
	if (chdir(search_envp("OLDPWD", copy_env)) == 0)
	{
		update_oldpwd("OLDPWD", cwd, copy_env);
		return (0);
	}
	else
	{
		perror("OLDPWD not set");
		return (1);
	}
}

int	get_prefix_length(char *line_read)
{
	int	len;

	len = 0;
	while (line_read[len] && line_read[len] != '=')
		len++;
	return (len);
}

char	*search_envp(char *line_read, char **copy_env)
{
	int	len;
	int	is_index;

	len = get_prefix_length(line_read);
	is_index = is_match(line_read, copy_env);
	if (is_index == -1)
		return (NULL);
	return (copy_env[is_index] + len + 1);
}
