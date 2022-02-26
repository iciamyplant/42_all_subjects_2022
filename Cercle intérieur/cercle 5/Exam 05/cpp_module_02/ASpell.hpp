/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 23:06:00 by ncolomer          #+#    #+#             */
/*   Updated: 2020/02/11 11:41:51 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASPELL_HPP
# define ASPELL_HPP

# include <iostream>
# include <string>

class ATarget;

class ASpell
{
protected:
	std::string name;
	std::string effects;
public:
	ASpell();
	ASpell(std::string const &name, std::string const &effects);
	ASpell(ASpell const &other);
	virtual ~ASpell();

	ASpell &operator=(ASpell const &other);

	std::string const &getName(void) const;
	std::string const &getEffects(void) const;

	void launch(ATarget const &target);

	virtual ASpell *clone(void) const = 0;
};

# include "ATarget.hpp"

#endif
