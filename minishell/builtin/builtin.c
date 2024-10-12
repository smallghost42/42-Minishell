/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 08:53:49 by ferafano          #+#    #+#             */
/*   Updated: 2024/10/04 11:36:05 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int	ft_echo(char **argv)
{
	int	i;
	int	j;
	int	nl;
	int	status;

	i = 1;
	nl = 0;
	status = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			j = 1;
			while (argv[i][j])
			{
				if (argv[i][j] && argv[i][j] == 'n')
				{
					nl = 1;
					j++;
				}
				else if (argv[i][j] && argv[i][j] != 'n')
				{
					write(2, "echo: invalid flag\n", 19);
					nl = 2;
					break ;
				}
			}
		}
		else
			break ;
		if (nl == 2)
			return (1);
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		i++;
	}
	if (nl == 1)
		printf("\n");
	return (status);
}

int	ft_exit(char **argv)
{
	if (argv[1] && argv[2] != NULL)
	{
		write(2, "exit: too many arguments\n", 24);
		return (1);
	}
	else
		exit(0);
	return (0);
}

int	buildin(char **argv, char ***copy_env)
{
	int	status;

	status = 0;
	if (strcmp(argv[0], "cd") == 0)
		status = ft_cd(argv, *copy_env);
	else if (strcmp(argv[0], "pwd") == 0)
		status = ft_pwd(argv);
	else if (strcmp(argv[0], "env") == 0)
		status = ft_env(*copy_env, argv);
	else if (strcmp(argv[0], "unset") == 0)
		status = ft_unset(argv, &*copy_env);
	else if (strcmp(argv[0], "export") == 0)
		status = ft_export(argv, &*copy_env);
	else if (strcmp(argv[0], "echo") == 0)
		status = ft_echo(argv);
	else if (strcmp(argv[0], "get_env") == 0)
		status = get_env_value(argv, *copy_env);
	else if (strcmp(argv[0], "exit") == 0)
		status = ft_exit(argv);
	else
	{
		printf("not a building | cmd : %s | args : %s\n", argv[0], argv[1]);
		status = 1;
	}
	printf("status : %d \n", status);
	return (status);
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	char	*line_read;
// 	char	**copy_env;
// 	char	**args;

// 	(void)argc;
// 	(void)argv;
// 	line_read = NULL;
// 	copy_env = ft_copy_env(envp);
// 	args = malloc(sizeof(char *));
// 	while (1)
// 	{
// 		if (line_read)
// 		{
// 			free(line_read);
// 			line_read = NULL;
// 		}
// 		pwd_prompt("pwd");
// 		line_read = readline("\n\033[0;35m❯ \033[0m");
// 		add_history(line_read);
// 		args = ft_split(line_read, ' ');
// 		buildin(args, &copy_env);
// 	}
// 	for (int i = 0; copy_env[i]; i++)
// 		free(copy_env[i]);
// 	free(copy_env);
// 	return (0);
// }