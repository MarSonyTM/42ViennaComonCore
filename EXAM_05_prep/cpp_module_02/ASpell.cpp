#include "ASpell.hpp"
#include "ATarget.hpp"

ASpell::ASpell() {}

ASpell::ASpell(const std::string& _name, const std::string& _effects) 
    : name(_name), effects(_effects) {}

ASpell::ASpell(const ASpell& other) {
    *this = other;
}

ASpell& ASpell::operator=(const ASpell& other) {
    if (this != &other) {
        name = other.name;
        effects = other.effects;
    }
    return *this;
}

ASpell::~ASpell() {}

const std::string& ASpell::getName() const {
    return name;
}

const std::string& ASpell::getEffects() const {
    return effects;
}

void ASpell::launch(const ATarget& target) const {
    target.getHitBySpell(*this);
} 