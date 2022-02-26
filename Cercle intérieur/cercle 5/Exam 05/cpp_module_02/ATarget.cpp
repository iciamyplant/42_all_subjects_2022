/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 23:26:40 by ncolomer          #+#    #+#             */
/*   Updated: 2020/02/13 16:40:16 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATarget.hpp"

ATarget::ATarget():
	type() {}

ATarget::ATarget(std::string const &type):
	type(type) {}

ATarget::ATarget(ATarget const &other):
	type(other.type) {}

ATarget::~ATarget() {}

ATarget &ATarget::operator=(ATarget const &other) {
	this->type = other.type;
	return (*this);
}

std::string const &ATarget::getType(void) const {
	return (this->type);
}

void ATarget::getHitBySpell(ASpell const &spell) const {
	std::cout << this->type << " has been " << spell.getEffects() << "!\n";
}
