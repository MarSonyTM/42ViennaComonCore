#include "Intern.hpp"

Intern::Intern() {}

Intern::Intern(Intern const &other) 
{
    (void)other;  // Intern has no attributes to copy
}

Intern &Intern::operator=(Intern const &other) 
{
    (void)other;  // Intern has no attributes to assign
    return *this;
}

Intern::~Intern() {}

// Form creation methods
AForm* Intern::createShrubberyForm(std::string const &target) const 
{
    return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomyForm(std::string const &target) const 
{
    return new RobotomyRequestForm(target);
}

AForm* Intern::createPresidentialForm(std::string const &target) const 
{
    return new PresidentialPardonForm(target);
}

const char *Intern::FormNotFoundException::what() const throw()
    {
        return ("Form type not found!");
    }

AForm* Intern::makeForm(std::string const &formName, std::string const &target) const 
{
    // Array of form types and their creation methods
    static const FormType forms[] = {
        {"shrubbery creation", &Intern::createShrubberyForm},
        {"robotomy request", &Intern::createRobotomyForm},
        {"presidential pardon", &Intern::createPresidentialForm}
    };

    // Look for matching form name
    for (int i = 0; i < 3; i++) {
        if (formName == forms[i].name) {
            AForm* form = (this->*forms[i].creator)(target);
            std::cout << "Intern creates " << form->getName() << std::endl;
            return form;
        }
    }
    // If no matching form found
    throw FormNotFoundException();
}
