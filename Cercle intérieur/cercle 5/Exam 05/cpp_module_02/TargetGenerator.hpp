/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TargetGenerator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:59:50 by ncolomer          #+#    #+#             */
/*   Updated: 2020/02/13 16:42:37 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TARGETGENERATOR_HPP
# define TARGETGENERATOR_HPP

# include <vector>
# include "ATarget.hpp"

class TargetGenerator
{
private:
	std::vector<ATarget*> types;
public:
	TargetGenerator();
	virtual ~TargetGenerator();

	void learnTargetType(ATarget *type);
	void forgetTargetType(std::string const &name);
	ATarget *createTarget(std::string const &name);
};

#endif
