/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:03:37 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/12 10:28:16 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H

# define EXECUTER_H

# include "../header.h"

void	execute(t_sh_params **sh_params);
int		handle_stdin(t_cmd *cmd);
int		handle_stdout(t_cmd *cmd);

#endif