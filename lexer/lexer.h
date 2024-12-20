/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:35:02 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/04 14:57:03 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# include "../builtin/buildin.h"
# include "../header.h"
# include "../parser/parser.h"

typedef struct s_expand
{
	char	*value;
	int		index;
}			t_expand;

t_token		*lex(char *input, t_sh_params **shell_params);
void		add_token(t_token **tk, t_token_type type, char *str, int len);
int			take_word_len(char *str, int i);
int			is_operator(char c);
int			idx_of_first(char *str, char c);
int			is_redir(t_token *tk);
int			lex_operator(char *str, t_token **tk);
t_token		*tk_create(char *value, t_token_type type, t_token *tk_prev);
t_token		*tk_last(t_token *tk);
void		tk_add_back(t_token **tk, t_token *tk_new);
void		tk_clear(t_token **tk);
int			check_tk_error(t_token **tk, t_sh_params **shell_params);
int			redir_error(t_token **tk);
int			my_perror(int status, char *str);
void		expand(t_token **tk, t_sh_params *shell_params);
int			expand_params(char *value, char **new_value, int i,
				t_sh_params *shell_params);
int			expand_single_quote(char *value, char **new_value, int i);
int			expand_double_quote(char *value, char **new_value, int i,
				t_sh_params *shell_params);
char		*join_char(char *new_value, char c);
void		update_tk(t_token **tk, t_list **lst_word, char **new_value,
				char **value);
int			handle_params(t_list **lst_word, char *value, char **new_value,
				t_sh_params *shell_params);
char		*my_getenv(char *var, t_sh_params *shell_params);

#endif