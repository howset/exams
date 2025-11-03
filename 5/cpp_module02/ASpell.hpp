#pragma once

#include <iostream>
class ATarget;

class ASpell
{
	protected:
		std::string _name;
		std::string _effects;
	public:
		ASpell(const std::string &name, const std::string &title);
		virtual ~ASpell();
		std::string getName() const;
		std::string getEffects() const;
		virtual ASpell *clone() const = 0;
		void launch(const ATarget &src) const;
};
