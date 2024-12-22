#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <fstream>

class ExamSimulator {
private:
    std::vector<std::string> exercises = {
        "cpp_module_00 - Basic Warlock",
        "cpp_module_01 - Warlock with Spells",
        "cpp_module_02 - Advanced Spell Management"
    };

    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void printExercise(const std::string& exercise) {
        if (exercise == "cpp_module_00 - Basic Warlock") {
            std::cout << "\nCreate a Warlock class with:\n";
            std::cout << "- Private attributes: name and title (strings)\n";
            std::cout << "- No default constructor\n";
            std::cout << "- No copy constructor/assignment\n";
            std::cout << "- Constructor with name and title\n";
            std::cout << "- Destructor\n";
            std::cout << "- getName() and getTitle() const methods\n";
            std::cout << "- setTitle() method\n";
            std::cout << "- introduce() method\n\n";
            std::cout << "Expected output examples:\n";
            std::cout << "Richard: This looks like another boring day.\n";
            std::cout << "Richard: I am Richard, Mistress of Magma!\n";
            std::cout << "Richard: My job here is done!\n";
        }
        else if (exercise == "cpp_module_01 - Warlock with Spells") {
            std::cout << "\nCreate the following classes:\n";
            std::cout << "1. ASpell (abstract):\n";
            std::cout << "   - name and effects attributes\n";
            std::cout << "   - pure virtual clone() method\n";
            std::cout << "2. ATarget (abstract):\n";
            std::cout << "   - type attribute\n";
            std::cout << "   - pure virtual clone() method\n";
            std::cout << "3. Fwoosh (concrete spell):\n";
            std::cout << "   - name: \"Fwoosh\"\n";
            std::cout << "   - effects: \"fwooshed\"\n";
            std::cout << "4. Dummy (concrete target):\n";
            std::cout << "   - type: \"Target Practice Dummy\"\n";
            std::cout << "5. Modify Warlock:\n";
            std::cout << "   - Add spell management\n";
            std::cout << "   - learnSpell(), forgetSpell(), launchSpell()\n";
        }
        else if (exercise == "cpp_module_02 - Advanced Spell Management") {
            std::cout << "\nAdd the following:\n";
            std::cout << "1. New Spells:\n";
            std::cout << "   - Fireball (\"burnt to a crisp\")\n";
            std::cout << "   - Polymorph (\"turned into a critter\")\n";
            std::cout << "2. New Target:\n";
            std::cout << "   - BrickWall (\"Inconspicuous Red-brick Wall\")\n";
            std::cout << "3. SpellBook class:\n";
            std::cout << "   - No copy\n";
            std::cout << "   - Manage spells (learn/forget/create)\n";
            std::cout << "4. TargetGenerator class:\n";
            std::cout << "   - No copy\n";
            std::cout << "   - Manage targets (learn/forget/create)\n";
            std::cout << "5. Modify Warlock:\n";
            std::cout << "   - Use SpellBook instead of direct spell management\n";
        }
    }

    void startTimer(int minutes) {
        while (minutes > 0) {
            clearScreen();
            std::cout << "\nTime remaining: " << minutes << " minutes\n";
            std::this_thread::sleep_for(std::chrono::minutes(1));
            minutes--;
        }
        clearScreen();
        std::cout << "\nTime's up! Exercise completed.\n";
    }

    void createDirectory(const std::string& exercise) {
        std::string cmd = "mkdir -p " + exercise;
        system(cmd.c_str());
    }

public:
    void run() {
        while (true) {
            clearScreen();
            std::cout << "\n=== 42 Exam Rank 05 Simulator ===\n\n";
            std::cout << "Available exercises:\n";
            for (size_t i = 0; i < exercises.size(); ++i) {
                std::cout << i + 1 << ". " << exercises[i] << "\n";
            }
            std::cout << "0. Exit\n\n";
            
            int choice;
            std::cout << "Choose an exercise (0-" << exercises.size() << "): ";
            std::cin >> choice;

            if (choice == 0) break;
            if (choice < 1 || choice > static_cast<int>(exercises.size())) continue;

            clearScreen();
            std::string selectedExercise = exercises[choice - 1];
            std::cout << "\nSelected exercise: " << selectedExercise << "\n";
            printExercise(selectedExercise);

            std::cout << "\nOptions:\n";
            std::cout << "1. Start exercise with timer (45 minutes)\n";
            std::cout << "2. View exercise requirements\n";
            std::cout << "3. Create exercise directory\n";
            std::cout << "0. Back to main menu\n\n";
            
            int option;
            std::cout << "Choose an option: ";
            std::cin >> option;

            switch (option) {
                case 1:
                    std::cout << "\nStarting exercise timer (45 minutes)...\n";
                    startTimer(45);
                    break;
                case 2:
                    clearScreen();
                    printExercise(selectedExercise);
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(2);
                    break;
                case 3:
                    createDirectory("cpp_module_0" + std::to_string(choice - 1));
                    std::cout << "\nDirectory created!\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    break;
                case 0:
                    break;
            }
        }
    }
};

int main() {
    ExamSimulator simulator;
    simulator.run();
    return 0;
} 