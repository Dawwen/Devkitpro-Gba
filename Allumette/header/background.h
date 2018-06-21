/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 21:45:30 by olivier           #+#    #+#             */
/*   Updated: 2018/06/21 21:50:59 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKGROUND_H
#define BACKGROUND_H

/* the width and height of the screen */
#define WIDTH 240
#define HEIGHT 160

/* palette is always 256 colors */
#define PALETTE_SIZE 256

/* return a pointer to one of the 4 character blocks (0-3) */
static inline volatile unsigned short* char_block(unsigned long block) {
	/* they are each 16K big */
	return (volatile unsigned short*) (0x6000000 + (block * 0x4000));
}

/* return a pointer to one of the 32 screen blocks (0-31) */
static inline volatile unsigned short* screen_block(unsigned long block) {
	/* they are each 2K big */
	return (volatile unsigned short*) (0x6000000 + (block * 0x800));
}

#endif
