#pragma once

#include <iostream>
#include <map>
#include "SpellBook.hpp"

class ASpell;
class ATarget;

class Warlock
{
	private:
		std::string _name;
		std::string _title;
		SpellBook spellBook;
	public:
	    Warlock(const std::string &name, const std::string &title);
	    ~Warlock();
		const std::string &getName() const;
		const std::string &getTitle() const;
		void setTitle(const std::string &title);
		void introduce() const;

		void learnSpell(ASpell *);
		void forgetSpell(std::string);
		void launchSpell(std::string, const ATarget &);
};
