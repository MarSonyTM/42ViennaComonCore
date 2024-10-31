/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:26:16 by marianfurni       #+#    #+#             */
/*   Updated: 2024/10/31 16:27:55 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm()
    : AForm("ShrubberyCreationForm", 145, 137), _target("Default") {}

ShrubberyCreationForm::ShrubberyCreationForm(std::string const &target) 
        : AForm("ShrubberyCreationForm", 145, 137), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &other)
    : AForm(other), _target(other._target) {}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &other) {
    if (this != &other) {
        AForm::operator=(other);
        _target = other._target;
    }
    return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

const char *ShrubberyCreationForm::FileOpenException::what() const throw()
{
    return ("Could not create shrubbery file");
}

const char *ShrubberyCreationForm::FileWriteException::what() const throw()
{
    return ("Could not write to shrubbery file");
}

void ShrubberyCreationForm::performAction() const
{
    std::ofstream ofs((_target + "_shrubbery").c_str());
    if (!ofs.is_open()) {
        throw FileOpenException();
    }
    ofs << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣆⠀⠀⢻⡍⢳⡄⠀⠀⣿⠸⣆⠀⠀⣠⣤⣾⢳⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⢀⣀⠀⢀⠀⢀⣀⠀⢸⢁⣿⡄⠀⠈⢷⣈⣿⠀⣠⣼⣦⣿⣴⣋⣡⠞⢻⠀⣿⢀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠘⢿⡻⣿⠳⣾⡍⠻⣿⣾⢿⡛⠶⣦⡄⠈⣿⣏⣡⠞⠋⣻⠉⠉⡀⠀⢸⡶⢟⣽⡯⠥⢤⣄⣀⡀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⢀⣈⣛⣿⠀⢹⡿⠶⣼⣿⠀⠙⠶⢬⣷⣿⢸⡏⠀⠀⠀⡟⠀⢸⠹⣦⣾⠞⠋⠉⠛⠛⢿⠋⣻⠷⢲⣶⠆⠀⠀⠀\n"
           "⠀⠀⠀⢼⡿⣦⠸⣯⡉⠛⠷⣾⡃⠀⠀⢸⣇⠀⠀⠀⠈⣽⡇⢿⡄⠀⢀⡇⠀⢸⣠⡟⠀⠀⠀⠀⠀⠀⣸⣾⠥⠖⠋⠀⠀⠀⠀⠀\n"
           "⠀⠀⢰⣾⣧⢻⡆⠈⠉⠉⠙⠙⠻⣦⣀⠀⢿⣄⠀⠀⠀⣿⡇⠈⢻⣆⢸⡇⠀⣸⣿⢦⡀⠀⠀⣀⣤⣾⠋⠀⣀⣤⣶⣞⣉⡿⠆⠀\n"
           "⠀⠀⠘⣧⠈⢿⡃⠀⣀⣤⣤⣀⠀⠀⠙⠳⢶⣿⣦⡀⠀⣿⡇⠀⠀⢻⣿⣧⠞⢉⣿⣄⢻⡖⠛⠉⠉⠉⠉⠻⣿⣍⠛⣧⡀⠀⠀⠀\n"
           "⠀⢸⡿⢿⡷⠴⢷⡾⠥⠴⠞⠁⠀⠀⠀⠀⠀⠀⠉⠻⣦⣹⣇⠀⠀⠈⣿⡇⢀⡾⠉⣯⠛⠇⠀⠀⠀⠀⣀⣠⠞⠋⠓⠛⠟⠀⠀⠀\n"
           "⠀⠈⢷⡈⣷⡀⠈⠻⣆⠀⠀⢀⣠⡤⢤⣤⠀⠀⠀⠀⠘⢿⣿⡄⠀⠀⣼⣷⠋⢹⡀⣿⣀⣤⡤⠶⠒⠋⠹⣍⠳⣄⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠙⢿⣀⠀⠀⠙⠿⣦⡛⠛⠛⠛⠁⠀⠀⠀⠀⠀⠈⢿⣧⣴⠟⢻⡇⢀⣤⠿⣿⣉⡀⠀⠀⣀⡀⠀⠈⠛⠛⠃⠀⢀⣠⣤⠀\n"
           "⠀⠀⠀⠀⠀⠉⠙⠛⠲⠶⠿⠿⣦⣄⣀⣀⣀⣀⣀⠀⠀⠀⢸⣿⠏⠀⢸⣷⠋⠁⠀⠀⠉⠉⠛⠛⣿⠙⢲⡄⠀⣀⣴⣾⡽⠾⠛⠀\n"
           "⢰⢦⣄⠀⠀⢴⣚⣛⣶⣶⠀⠀⠀⠉⠛⠛⠻⠿⠿⠿⣷⣦⣼⣿⡄⠀⣿⡇⠀⠀⠀⠀⠀⣀⣀⣤⣬⡿⠶⠛⢩⣿⢯⣉⠛⢶⡄⠀\n"
           "⠘⢦⣌⣷⡄⠀⠀⠀⠀⠙⢶⣤⣀⡀⠀⠀⣀⣀⣀⣀⠈⠛⣿⣿⠇⣰⣿⣧⣶⣾⣿⠿⠿⠛⠉⠘⣧⢻⡄⠀⣾⢹⡆⠈⠙⠛⠛⠀\n"
           "⠀⠀⢈⡛⠷⠦⣤⣤⣤⡤⠴⠿⠿⠛⠛⠛⠋⠛⠛⠻⢿⣦⣼⣿⣠⣿⠋⠁⠀⠉⠙⠛⢳⣶⡞⠛⠻⣾⡏⠙⢿⡿⣧⣴⣶⠶⢤⣀\n"
           "⠀⠀⡟⢹⡄⠀⠀⠀⠀⡞⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣿⣿⣿⡏⠀⠀⠀⠀⠀⠀⢸⣁⣿⠀⠀⠀⠀⠀⠀⠀⠙⢷⡈⠻⣞⠉\n"
           "⠀⠀⢷⡾⠀⠀⠀⠀⠀⠻⣼⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠘⠿⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠛⠿⠀\n"
           "⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣷⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣿⠟⠛⢻⣯⠙⠻⠿⠿⠷⣦⣄                  \n";
    if (!ofs) {
        throw FileWriteException();
    }
    ofs.close();
}


