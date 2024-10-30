/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:14:28 by ferafano          #+#    #+#             */
/*   Updated: 2024/10/29 18:28:13 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int	unset_nb(char **argv, char **env)
{
	int		i;
	int		j;
	int		count;
	char	*tmp;

	i = 0;
	count = 0;
	while (argv[i])
	{
		tmp = ft_strdup(argv[i]);
		tmp = ft_strjoin(tmp, "=");
		j = 0;
		while (env[j])
		{
			if (ft_strncmp(argv[i], env[j], ft_strlen(argv[i])) == 0)
			{
				count++;
				break ;
			}
			j++;
		}
		free(tmp);
		i++;
	}
	return (count);
}

int	is_to_unset(char *str, char **argv)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	tmp = ft_strdup(str);
	tmp[i] = '\0';
	i = 0;
	while (argv[i])
	{
		if (ft_strcmp(tmp, argv[i]) == 0)
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

int	ft_unset(char **argv, char ***copy_env)
{
	int		nb_to_unset;
	int		len;
	int		i;
	char	**new;

	len = 0;
	while ((*copy_env)[len])
		len++;
	nb_to_unset = unset_nb(argv, *copy_env);
	if (nb_to_unset == 0)
		return (0);
	new = malloc(sizeof(char *) * (len - nb_to_unset + 1));
	len = 0;
	i = 0;
	while ((*copy_env)[len])
	{
		if (!is_to_unset((*copy_env)[len], argv))
		{
			new[i] = ft_strdup((*copy_env)[len]);
			i++;
		}		
		len++;
	}
	new[i] = NULL;
	free_args(*copy_env);
	*copy_env = new;
	return (0);
}
