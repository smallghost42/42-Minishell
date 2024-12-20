/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:12:15 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/05 14:56:55 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	expansion_lst(t_list **lst_word, char **split_value)
{
	int		i;
	char	*content;

	if (!split_value || split_value[0] == NULL)
		return ;
	if (*lst_word != NULL && (*lst_word)->content != NULL
		&& split_value[0] != NULL)
	{
		content = ft_lstlast(*lst_word)->content;
		ft_lstlast(*lst_word)->content = ft_strjoin(content, split_value[0]);
	}
	if (!*lst_word && split_value[0] != NULL)
		*lst_word = ft_lstnew(ft_strdup(split_value[0]));
	i = 1;
	while (split_value[i])
	{
		content = ft_strdup(split_value[i]);
		ft_lstadd_back(lst_word, ft_lstnew(content));
		i++;
	}
}

static char	**splitted_value(char *prev_val, char *new_value, t_list **lst_word)
{
	int		len;
	char	*content;
	char	*tmp;
	char	**tab;

	len = 0;
	tab = NULL;
	if (prev_val)
		len = ft_strlen(prev_val);
	tmp = new_value + len;
	tab = ft_split(new_value + len, ' ');
	if (prev_val != NULL && ft_strcmp(prev_val, "") != 0)
	{
		if (!*lst_word)
			ft_lstadd_back(lst_word, ft_lstnew(ft_strdup(prev_val)));
		else
		{
			content = ft_lstlast(*lst_word)->content;
			ft_lstlast(*lst_word)->content = ft_strjoin(content, prev_val);
		}
	}
	if (new_value && tmp[0] == ' ' && !ft_is_blank(tmp))
		ft_lstadd_back(lst_word, ft_lstnew(ft_strdup("")));
	return (tab);
}

int	handle_params(t_list **lst_word, char *value, char **new_value,
		t_sh_params *shell_params)
{
	int		i;
	int		new_val_len;
	char	**split_value;
	char	*prev_val;

	prev_val = ft_strdup(*new_value);
	i = expand_params(value, new_value, 0, shell_params);
	split_value = splitted_value(prev_val, *new_value, lst_word);
	if (prev_val)
		free(prev_val);
	expansion_lst(lst_word, split_value);
	if (*new_value)
		new_val_len = ft_strlen(*new_value);
	if (value[i] && new_val_len > 0 && (*new_value)[new_val_len - 1] == ' ')
		ft_lstadd_back(lst_word, ft_lstnew(ft_strdup("")));
	if (split_value)
		free_args(split_value);
	free(*new_value);
	*new_value = NULL;
	if (value[i])
		*new_value = ft_strdup("");
	return (i);
}

static int	initial_check(t_token **tk, t_list **lst_word, char **new_value,
		char **value)
{
	t_list	*last_lst;
	char	*last_content;

	free(*value);
	(*tk)->value = NULL;
	if (!*lst_word)
	{
		if (*new_value)
			(*tk)->value = *new_value;
		return (1);
	}
	if (*lst_word && *new_value && (*lst_word)->content)
	{
		last_lst = ft_lstlast(*lst_word);
		last_content = last_lst->content;
		ft_lstlast(*lst_word)->content = (void *)ft_strjoin(last_content,
			*new_value);
	}
	free(*new_value);
	return (0);
}

void	update_tk(t_token **tk, t_list **lst_word, char **new_value,
		char **value)
{
	t_token	*next;
	t_token	*new;
	t_list	*tmp_lst;
	char	*content;

	new = NULL;
	if (initial_check(tk, lst_word, new_value, value))
		return ;
	content = (*lst_word)->content;
	new = tk_create(ft_strdup(content), TK_E_WORD, (*tk)->prev);
	tmp_lst = (*lst_word)->next;
	while (tmp_lst)
	{
		content = ft_strdup(tmp_lst->content);
		tk_add_back(&new, tk_create(content, TK_E_WORD, tk_last(new)));
		tmp_lst = tmp_lst->next;
	}
	next = (*tk)->next;
	if (next)
		next->prev = new;
	tk_add_back(&new, next);
	free(*tk);
	*tk = new;
	ft_lstclear(lst_word, free_assign);
}
