#include "SpellBook.hpp"
#include "ASpell.hpp"

SpellBook::SpellBook()
{}

SpellBook::~SpellBook()
{
    _SpellBook.clear();
}

void SpellBook::learnSpell(ASpell *spell)
{
    if (spell != nullptr)
    {
        std::map<std::string, ASpell *>::iterator it = _SpellBook.find(spell->getName());

        if (it == _SpellBook.end())
            _SpellBook[spell->getName()] = spell->clone();
    }
}

void SpellBook::forgetSpell(const std::string &spellName)
{
    std::map<std::string, ASpell *>::iterator it = _SpellBook.find(spellName);

    if (it != _SpellBook.end())
    {
        delete it->second;
        _SpellBook.erase(spellName);
    }
}

ASpell *SpellBook::createSpell(const std::string &spellName)
{
    std::map<std::string, ASpell *>::iterator it = _SpellBook.find(spellName);

    if (it != _SpellBook.end())
        return (it->second->clone());
    return nullptr;
}
