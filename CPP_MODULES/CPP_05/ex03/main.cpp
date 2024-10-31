#include "Intern.hpp"

int main() {
    try {
        Intern someRandomIntern;
        AForm* rrf;

        // Create a robotomy request form
        rrf = someRandomIntern.makeForm("robotomy request", "Bender");
        
        // Use the form
        Bureaucrat boss("Boss", 1);
        boss.signForm(*rrf);
        boss.executeForm(*rrf);

        delete rrf;  // Don't forget to clean up!

        // Try to create an invalid form
        AForm* invalid = someRandomIntern.makeForm("invalid form", "target");
        delete invalid;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return (0);
} 


/*
                The mandatory part sounded simple but !
                Implementation of the Intern class was a bit tricky.
                I had to create a struct with a function pointer to the form creation methods.
                Then I had to create a map with the form names and the corresponding creation methods.
                Then I had to iterate over the map to find the form name and call the corresponding creation method.
*/