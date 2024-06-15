/**********************************************************
 // -> : ██████╗ █████╗ ███████╗███████╗ █████╗ ██████╗ 
        ██╔════╝██╔══██╗██╔════╝██╔════╝██╔══██╗██╔══██╗ 
        ██║     ███████║█████╗  ███████╗███████║██████╔╝ 
        ██║     ██╔══██║██╔══╝  ╚════██║██╔══██║██╔══██╗ 
        ╚██████╗██║  ██║███████╗███████║██║  ██║██║  ██║ 
         ╚═════╝╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝
 // -> Author:        mabahani
 // -> Modified by:   CZAR
 // -> Modified time: 2024-06-05 15:05:29
 **********************************************************/

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
    this->isSorted = 0;
}

PmergeMe::~PmergeMe(){
}

PmergeMe::PmergeMe(const PmergeMe& other){
    *this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other){
    (void)other;
    return(*this);
}

int PmergeMe::strToDouble(std::string test){
    std::stringstream ss;
    double var;
    ss << test;
    ss >> var;
    if (var > 2147483647)
        throw std::runtime_error("to big number");
    return var;
}

bool isVecSorted(const std::vector<int>& vec) {
    for (size_t i = 1; i < vec.size(); i++)
    {
        if(vec[i] < vec[i - 1])
            return false;
    }
    return true;
}

void PmergeMe::parser(int argc, char** argv)
{
    int n;
    std::stringstream ss;
    std::string temp;

    for (int i = 1; i < argc; i++)
    {
        ss << argv[i] << " ";
    }
    while(ss >> temp)
    {
        if(temp.empty() || temp.find_first_not_of("0123456789") != std::string::npos)
        {
            if(!temp.empty() && !(temp[0] == '+' && (temp).find_first_not_of("0123456789", 1) == std::string::npos))
                throw std::runtime_error("Invalid input");
        }
        n = strToDouble(temp);
        vec_t.push_back(n);
    }
    if (isVecSorted(vec_t))
        this->isSorted = 1;
    std::cout << "Before: ";
    for (size_t i = 0; i < vec_t.size(); i++)
    {
        std::cout << vec_t[i] << " ";
    }
    std::cout << std::endl;
}

int PmergeMe::returnIndexVector(std::vector<int> &v, int value){
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i] >= value && v[i-1] && v[i-1] < value)
        {
            return (i + 1);
        }
    }
    return -1;
}

std::vector<unsigned long> PmergeMe::jacobIndexGeneratorVector(std::vector<int> &jacobsthals, int size){
    std::vector<unsigned long> jacobsthals_indexed;
    int jacob = 0;
    for (size_t i = 0; i < jacobsthals.size(); i++)
    {
        jacob = jacobsthals[i];
        if (jacob <= size)
            jacobsthals_indexed.push_back(jacob);
        while (jacob > 0 && jacobsthals[i] != 1 && std::find(jacobsthals_indexed.begin(), jacobsthals_indexed.end(), --jacob) == jacobsthals_indexed.end())
        {
            if (jacob > size)
            {
                continue;
            }
            jacobsthals_indexed.push_back(jacob);
        }
    }
    // remove one 1 from the beginning of the sequence
    jacobsthals_indexed.erase(jacobsthals_indexed.begin());
    return jacobsthals_indexed;
}

int PmergeMe::Jacobsthal(int n)
{
    if (n == 0)
        return 0;
 
    if (n == 1)
        return 1;
 
    return Jacobsthal(n - 1) + 2 * Jacobsthal(n - 2);
}

void PmergeMe::mergeVector(std::vector<std::pair<int, int> >& arr, int left, int mid, int right){
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<std::pair<int, int> > L(n1), R(n2);

    for (i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    i = j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i].first <= R[j].first) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }   
}

void PmergeMe::mergeSortVector(std::vector<std::pair<int, int> >& arr, int left, int right){
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortVector(arr, left, mid);
        mergeSortVector(arr, mid + 1, right);
        mergeVector(arr, left, mid, right);
    }
}

void PmergeMe::recursiveSortVector(std::vector<std::pair<int,int> > &couples){
    //not used => std::vector<int> couple;
    for (size_t i = 0; i < couples.size(); i++)
    {
        if (couples[i].first < couples[i].second)
        {
            std::swap(couples[i].first, couples[i].second);
        }
    }
    mergeSortVector(couples, 0, couples.size() - 1);
}

void print_vector(std::vector<int> &v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

std::vector<int>  PmergeMe::mainHubVector(){
    //check if already sorted
    if(isSorted == 1)
        return vec_t;
    //step one
    std::vector<std::pair<int,int> > couples;
    std::vector<int> struggling;

    if (vec_t.size() % 2 != 0)
    {
        struggling.push_back(vec_t.back());
        vec_t.pop_back();
    }

    // Split the sequence into couples
    for (size_t i = 0; i < vec_t.size(); i += 2)
    {
        // make pairs of couples
        couples.push_back(std::make_pair(vec_t[i], vec_t[i + 1]));

    }
    
    // sort couples recursively ps:removed the t vector for that call it's useless
    recursiveSortVector(couples);

    //step Two
    std::vector<int> smallest;
    std::vector<int> largest;
    for (size_t i = 0; i < couples.size(); i++)
    {
        smallest.push_back(couples[i].second);
        largest.push_back(couples[i].first);    
    }

    //step three
    if(smallest.size() >= 2){       
        std::vector<int> jacobsthals;
        std::vector<unsigned long> jacobsthals_indexed;
        unsigned long jacob = 0;
        for (size_t i = 2; i < smallest.size() + largest.size(); i++)
        {
            jacob = Jacobsthal(i);
            if (jacob > smallest.size())
            {
            jacobsthals.push_back(jacob);
                break;
            }
            jacobsthals.push_back(jacob);
        }
        jacobsthals_indexed = jacobIndexGeneratorVector(jacobsthals, smallest.size());

        //step four
        largest.insert(std::lower_bound(largest.begin(), largest.end(), smallest[0]), smallest[0]);

        //step five
        int last_size = 0;
        for (size_t i = 0; i < jacobsthals_indexed.size(); i++)
        {
            if (jacobsthals_indexed[i] <= smallest.size())
            {
                if (pow(2, returnIndexVector(jacobsthals,jacobsthals_indexed[i])) - 1 > largest.size())
                    last_size = largest.size();
                else
                    last_size = pow(2, returnIndexVector(jacobsthals,jacobsthals_indexed[i])) - 1;

                largest.insert(std::lower_bound(largest.begin(), largest.begin() + last_size, smallest[jacobsthals_indexed[i] - 1]), smallest[jacobsthals_indexed[i] - 1]);
            }
        }
    } else {
        largest.insert(std::lower_bound(largest.begin(), largest.end(), smallest[0]), smallest[0]);
    }

    //step six
    if (!struggling.empty())
    {
        largest.insert(std::lower_bound(largest.begin(), largest.end(), struggling[0]), struggling[0]);
    }

    return largest;
}