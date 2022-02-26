/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 00:35:12 by ncolomer          #+#    #+#             */
/*   Updated: 2020/02/04 13:09:40 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Warlock.hpp"
#include "Dummy.hpp"
#include "Fwoosh.hpp"

int main(void)
{
	std::cout << "--- Constructors:\n";

	Warlock richard("Richard", "Master of the Universe");
	Fwoosh *spell = new Fwoosh();
	Dummy targetPractice;

	std::cout << "--- \"Fwoosh\" not learned:\n";

	richard.launchSpell("Fwoosh", targetPractice);

	std::cout << "--- \"Fwoosh\" learned:\n";

	richard.learnSpell(spell);
	richard.launchSpell("Fwoosh", targetPractice);

	std::cout << "--- Forgotten \"Fwoosh\":\n";

	richard.forgetSpell("Fwoosh");
	richard.launchSpell("Fwoosh", targetPractice);

	std::cout << "--- Non-existant spell:\n";

	richard.launchSpell("Splash", targetPractice);
	richard.forgetSpell("Splash");
	richard.launchSpell("Splash", targetPractice);

	std::cout << "--- Destructors:\n";
	return (0);
}
