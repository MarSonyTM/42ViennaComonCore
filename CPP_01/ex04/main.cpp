/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:27:58 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 14:29:22 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "replace.hpp"
#include <iostream>
#include <fstream> // std::ifstream, std::ofstream functions to read and write files
#include <sstream> // std::stringstream function to read the file content

int main(int argc, char **argv)
{
    if (argc != 4 || !argv[1][0] || !argv[2][0]) // check if the number of arguments is correct
    {
        if (argc != 4)
            std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
        else
            std::cerr << "Error: filename and strings cannot be empty" << std::endl;
        return (1);
    }

    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    std::ifstream inputFile(filename.c_str()); // open the file  in read mode
    
    if (!inputFile.is_open()) // check if the file is open
    {
        std::cout << "Error: could not open file" << std::endl;
        return (1);
    }
    std::stringstream buffer; // create a stringstream object to read the file content
    buffer << inputFile.rdbuf(); // reads the entire content of the file into the string stream buffer
    std::string content = buffer.str(); // convert the string stream buffer into a string
    inputFile.close(); // close the input file

    if(content.empty()) // check if the file is empty
    {
        std::cout << "Error: file is empty" << std::endl;
        return (1);
    }
    if (content.find(s1) == std::string::npos) // check if the string s1 is in the file
    {
        std::cout << "Error: string " << s1 << " not found in file" << std::endl;
        return (1);
    }
    replace(content, s1, s2);
    std::ofstream outputFile((filename + ".replace").c_str()); // create a new file in write mode ending with .replace
    if (!outputFile.is_open()) // check if the file can be open
    {
        std::cout << "Error: Could not create output file" << filename + ".replace" << std::endl;
        return (1);
    }
    outputFile << content; // write the content of the file into the output file
    outputFile.close(); // close the output file
    return (0);
}


/*std::ifstream: Used for reading from files.It opens a file in read mode
 and provides methods to check it the file is opne and to read data from the file
 
 std::ofstream: Used for writing to files.It opends a file in write mode
 and provides methos to check if the file is open and to weite data to the file*/