/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:36:00 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/24 09:54:01 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*parser_test(t_token *tk)
{
	t_cmd	*cmd;
	t_cmd	*new_cmd;

	cmd = NULL;
	while (tk)
	{
		if (tk->type != TK_PIPE)
		{
			new_cmd = cmd_create(tk);
			while (tk)
			{
				tk = tk->next;
				if (tk)
					if (tk->type == TK_PIPE)
						break;
			}
		}
		else
		{
			new_cmd = cmd_create(tk);
			tk = tk->next;
		}
		cmd_addback(&cmd, new_cmd);
	}
	return (cmd);
}
