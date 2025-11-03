#include "Warlock.hpp"
#include "ASpell.hpp"
#include "ATarget.hpp"

Warlock::Warlock(const std::string &name, const std::string &title): _name(name), _title(title)
{
    std::cout << getName() << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock()
{
    std::cout << getName() << ": My job here is done!" << std::endl;
}
const std::string &Warlock::getName() const
{
    return (this->_name);
}

const std::string &Warlock::getTitle() const
{
    return (this->_title);
}

void Warlock::setTitle(const std::string &title)
{
    this->_title = title;
}

void Warlock::introduce() const
{
    std::cout << getName() << ": I am " << getName() << ", " << getTitle() << "!" << std::endl;
}

void Warlock::learnSpell(ASpell *spell)
{
    spellBook.learnSpell(spell);
}

void Warlock::forgetSpell(std::string spellName)
{
    spellBook.forgetSpell(spellName);
}

void Warlock::launchSpell(std::string spellName, const ATarget &src)
{
    ASpell *spell = spellBook.createSpell(spellName);

    if (spell != nullptr)
    {
        spell->launch(src);
        delete spell;
    }
}
