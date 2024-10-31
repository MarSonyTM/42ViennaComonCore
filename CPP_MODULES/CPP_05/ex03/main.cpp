#include "Intern.hpp"

int main() {
    std::cout << "\n=== Basic Form Creation Tests ===\n" << std::endl;
    try {
        Intern someRandomIntern;
        Bureaucrat boss("Boss", 1);
        AForm* rrf;

        // Test successful form creation
        rrf = someRandomIntern.makeForm("robotomy request", "Bender");
        boss.signForm(*rrf);
        boss.executeForm(*rrf);
        delete rrf;

        // Test invalid form name
        std::cout << "\nTesting invalid form name:" << std::endl;
        AForm* invalid = someRandomIntern.makeForm("invalid form", "target");
        delete invalid;  // Won't be reached due to exception
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\n=== Testing All Form Types ===\n" << std::endl;
    try {
        Intern intern;
        Bureaucrat chief("Chief", 1);

        // Test all form types
        AForm* shrub = intern.makeForm("shrubbery creation", "Garden");
        AForm* robo = intern.makeForm("robotomy request", "R2D2");
        AForm* pres = intern.makeForm("presidential pardon", "Criminal");

        chief.signForm(*shrub);
        chief.signForm(*robo);
        chief.signForm(*pres);

        chief.executeForm(*shrub);
        chief.executeForm(*robo);
        chief.executeForm(*pres);

        delete shrub;
        delete robo;
        delete pres;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\n=== Edge Cases ===\n" << std::endl;
    try {
        Intern intern;
        Bureaucrat lowLevel("Intern", 150);

        // Test with empty strings
        std::cout << "Testing with empty form name:" << std::endl;
        AForm* empty = intern.makeForm("", "target");
        delete empty;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Intern intern;
        Bureaucrat lowLevel("Intern", 150);

        // Test with insufficient grade
        std::cout << "\nTesting with insufficient grade:" << std::endl;
        AForm* form = intern.makeForm("presidential pardon", "Criminal");
        lowLevel.signForm(*form);  // Should fail - grade too low
        lowLevel.executeForm(*form);  // Should fail - not signed and grade too low
        delete form;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\n=== Memory Management Test ===\n" << std::endl;
    try {
        Intern intern;
        // Create and immediately delete forms
        for (int i = 0; i < 3; i++) {
            AForm* form = intern.makeForm("robotomy request", "Test Subject " + std::to_string(i));
            delete form;
        }
        std::cout << "Memory management test completed successfully" << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
} 


/*
                The mandatory part sounded simple but !
                Implementation of the Intern class was a bit tricky.
                I had to create a struct with a function pointer to the form creation methods.
                Then I had to create a map with the form names and the corresponding creation methods.
                Then I had to iterate over the map to find the form name and call the corresponding creation method.
*/