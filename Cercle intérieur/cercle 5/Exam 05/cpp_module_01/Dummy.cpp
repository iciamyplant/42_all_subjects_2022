/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dummy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 23:16:30 by ncolomer          #+#    #+#             */
/*   Updated: 2020/02/13 16:41:43 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dummy.hpp"

Dummy::Dummy():
	ATarget("Dummy Practice") {}

Dummy::~Dummy() {}

ATarget *Dummy::clone(void) const {
	return (new Dummy(*this));
}
