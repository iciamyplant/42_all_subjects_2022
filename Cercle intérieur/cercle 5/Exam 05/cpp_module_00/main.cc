/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 00:33:40 by ncolomer          #+#    #+#             */
/*   Updated: 2020/02/04 13:11:01 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Warlock.hpp"

int main(void)
{
	std::cout << "--- Constructors:\n";
	// Warlock warlock; // Doesn't compile
	Warlock richard("Richard", "Master of the Universe");
	// Warlock warlock(richard); // Doesn't compile
	// Warlock warlock = richard; // Doesn't compile

	std::cout << "--- Introduce:\n";
	richard.introduce();

	std::cout << "--- New Title:\n";
	richard.setTitle("Master of the Earth");
	richard.introduce();

	std::cout << "--- Destructors:\n";
	return (0);
}
