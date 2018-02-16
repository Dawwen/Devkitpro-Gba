/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 19:39:52 by olivier           #+#    #+#             */
/*   Updated: 2018/02/04 22:08:10 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define linked_list struct Linked_list

struct Linked_list
{
	int lenght;
	void* data;
	linked_list* next;
};

linked_list* create_node(void* data, int lenght);
void push_back(linked_list **begin_list, void *data, int lenght);
void push_front(linked_list **begin_list, void *data, int lenght);
int get_data(linked_list **list, int global_index);
void set_data(linked_list **list, int index, int value);
void add_empty_node(linked_list** list, int lenght);

#endif
