/**********************************************************
 // -> : ██████╗ █████╗ ███████╗███████╗ █████╗ ██████╗ 
        ██╔════╝██╔══██╗██╔════╝██╔════╝██╔══██╗██╔══██╗ 
        ██║     ███████║█████╗  ███████╗███████║██████╔╝ 
        ██║     ██╔══██║██╔══╝  ╚════██║██╔══██║██╔══██╗ 
        ╚██████╗██║  ██║███████╗███████║██║  ██║██║  ██║ 
         ╚═════╝╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝
 // -> Author:        mabahani
 // -> Modified by:   CZAR
 // -> Modified time: 2024-06-05 19:15:08
 **********************************************************/

#include "PmergeMe.hpp"


int main(int argc, char **argv)
{
    PmergeMe fordJhonson;
    struct timeval startTimeVector, endTimeVector;
    try {
        if(argc <= 1)
            throw std::runtime_error("Usage: ./PmergeMe [numbers to sort ..]");
        if(argc == 2)
            throw std::runtime_error("nothing to sort");
        fordJhonson.parser(argc,argv);
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
        exit(3);
    }

    // Timing for std::vector
    gettimeofday(&startTimeVector, NULL);
    std::vector<int> vectorOne = fordJhonson.mainHubVector();
    gettimeofday(&endTimeVector, NULL);
    long durationVector = (endTimeVector.tv_sec - startTimeVector.tv_sec) * 1000000 + (endTimeVector.tv_usec - startTimeVector.tv_usec);
    
    std::cout << "after: ";
    for (size_t i = 0; i < vectorOne.size(); i++)
    {
        std::cout << vectorOne[i] << " ";
    }
    std::cout << std::endl;

    // Output timings
    std::cout.precision(6);
    std::cout << "Time to process a range of " << vectorOne.size() << " Time taken by std::vector: " << std::fixed << (double)durationVector << " us" << std::endl;
    return 0;
}