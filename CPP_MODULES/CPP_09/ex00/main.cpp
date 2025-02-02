/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:23:26 by marianfurni       #+#    #+#             */
/*   Updated: 2024/12/17 14:20:57 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: could not open file.\n Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    try {  //create BitcoinExchange object and load the database
        BitcoinExchange exchange("data.csv"); // loading the Bitcoin price database
        exchange.processInputFile(argv[1]); // processing the input file 
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl; 
        return 1;
    }

    return 0;
}


/*
     Using std::map because:                        key | value
     . perfect for storing data->price mapping    Date | value
     . automatically sorted by key
     . efficient for searching and retrieval
     . easy to find the closest date (findClosestDate)
*/