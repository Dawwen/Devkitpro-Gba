/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 11:42:48 by olivier           #+#    #+#             */
/*   Updated: 2018/08/29 16:00:58 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIST_H
# define LIST_H

typedef struct		s_list
{
	struct s_list	*next;
	void			*data;
}					t_list;

t_list	*create_elem(void *data);
void	list_push_back(t_list **begin_list, void *data);
void	list_push_front(t_list **begin_list, void *data);
int		list_size(t_list *begin_list);
void clear_list(t_list *list, void f(void*));

#endif
