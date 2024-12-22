#ifndef ATARGET_HPP
#define ATARGET_HPP

#include <string>
#include "ASpell.hpp"

class ATarget {
protected:
    std::string type;

public:
    ATarget();
    ATarget(const std::string& type);
    ATarget(const ATarget& other);
    ATarget& operator=(const ATarget& other);
    virtual ~ATarget();

    const std::string& getType() const;

    virtual ATarget* clone() const = 0;
    void getHitBySpell(const ASpell& spell) const;
};

#endif 