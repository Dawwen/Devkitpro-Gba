/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dico.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 19:39:52 by olivier           #+#    #+#             */
/*   Updated: 2018/03/21 13:35:07 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef dico_H
#define DICO_H

#define dico struct Dico

struct Dico
{
	int lenght;
	void* data;
	dico* next;
};

dico* create_node(void* data, int lenght);
void push_back(dico **begin_list, void *data, int lenght);
void push_front(dico **begin_list, void *data, int lenght);
int get_data(dico **list, int global_index);
void set_data(dico **list, int index, int value);
void add_empty_node(dico** list, int lenght);

#endif
