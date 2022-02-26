/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BrickWall.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:59:17 by ncolomer          #+#    #+#             */
/*   Updated: 2020/02/13 16:40:08 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BrickWall.hpp"

BrickWall::BrickWall():
	ATarget("BrickWall Practice") {}

BrickWall::~BrickWall() {}

ATarget *BrickWall::clone(void) const {
	return (new BrickWall(*this));
}
