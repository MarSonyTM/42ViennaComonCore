#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <string>
#include <iostream>
#include "ASpell.hpp"
#include "ATarget.hpp"
#include "SpellBook.hpp"

class Warlock {
private:
    std::string name;
    std::string title;
    SpellBook book;
    
    Warlock();
    Warlock(const Warlock& other);
    Warlock& operator=(const Warlock& other);

public:
    Warlock(const std::string& name, const std::string& title);
    ~Warlock();

    const std::string& getName() const;
    const std::string& getTitle() const;
    void setTitle(const std::string& title);
    void introduce() const;

    void learnSpell(ASpell* spell);
    void forgetSpell(std::string spellName);
    void launchSpell(std::string spellName, const ATarget& target);
};

#endif 