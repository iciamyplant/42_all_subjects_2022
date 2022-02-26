/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 20:37:27 by ncolomer          #+#    #+#             */
/*   Updated: 2020/02/04 13:02:29 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>
# include <string>
# include <vector>
# include "ASpell.hpp"
# include "ATarget.hpp"

class Warlock
{
private:
	std::string name;
	std::string title;

	std::vector<ASpell*> spells;

	Warlock();
	Warlock(Warlock const &other);

	Warlock &operator=(Warlock const &other);
public:
	Warlock(std::string const &name, std::string const &title);
	virtual ~Warlock();

	std::string const &getName(void) const;
	std::string const &getTitle(void) const;

	void setTitle(std::string const &title);

	void introduce(void) const;

	void learnSpell(ASpell *spell);
	void forgetSpell(std::string const &spellName);
	void launchSpell(std::string const &spellName, ATarget const &target);
};

#endif
