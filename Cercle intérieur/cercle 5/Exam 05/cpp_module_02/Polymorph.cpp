/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polymorph.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:49:28 by ncolomer          #+#    #+#             */
/*   Updated: 2020/02/13 16:39:49 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Polymorph.hpp"

Polymorph::Polymorph():
	ASpell("Polymorph", "turned to a sheep") {}

Polymorph::~Polymorph() {}

ASpell *Polymorph::clone(void) const {
	return (new Polymorph(*this));
}
