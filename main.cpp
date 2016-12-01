//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	ID Number - 1318804
//  main.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "small_dictionary.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Declarations
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

int distAlg (std::string A , std::string B);
bool existsInDictionary(const std::string &input,
                        const std::vector<std::string> &dict);
void optionsFunction(const int &option, const std::string &input,
                     const int &suggSize,
                     const std::vector<std::string> &suggestions);

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	main()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

int main (int argc, char *argv[])
{
    while(true)
    {
        std::string input;
        std::cout << std::endl;
        std::cout << "Please enter a word. To exit, type 'exitProg'";
        std::cout << std::endl;
        std::cin >> input;
        
        if (input == "exitProg")
        {
            return 0;
        }
        
        // Check to see if word is in dictionary
        bool found = existsInDictionary(input, Dict);
        if (found)
        {
            std::cout
            <<
            "Word found in dictionary, enter new word.\n"
            <<
            std::endl;
        }
        else
        {
            std::cout << "Word could not be found in the dictionary \n";
            std::vector<std::string> suggestions;
            
            // Creating suggestions
            int dictSize = Dict.size();
            for (int i = 0 ; i != dictSize ; ++i)
            {
                int dist = distAlg(input , Dict[i]);
                if (dist < input.size()*0.60)
                {
                    suggestions.push_back(Dict[i]);
                }
            }
            int suggSize = suggestions.size();
            if (suggSize > 0)
            {
                std::cout << "\nThe suggestions:\n";
                for (int i = 0 ; i != suggSize ; ++i)
                {
                    std::cout << i+1 << " - " << suggestions[i] << std::endl;
                    std::cout << std::endl;
                }
                std::cout << "Enter appropriate suggeston number. \n";
                std::cout << "For more options enter any key. \n";
            }
            int option;
            std::cin >> option;
            
            // Options after suggestions are given
            optionsFunction(option, input, suggSize, suggestions);
        }
    }
    return 0;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	optionsFunction()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void optionsFunction(const int &option, const std::string &input,
                     const int &suggSize,
                     const std::vector<std::string> &suggestions)
{
    bool furtherOptions = false;
    if(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
    }
    else if (option <= suggSize)
    {
        furtherOptions = true;
        std::cout << "The word is now : <"
        << suggestions[option-1] << ">\n";
    }
    if (furtherOptions == false)
    {
        std::string option, dictAdd="add";
        std::cout <<
        "\nTo include word to dictionary, enter 'add'.\n";
        std::cout << "To repeat programme, enter any key. \n " ;
        std::cin >> option;
        
        if (option == dictAdd)
        {
            Dict.push_back(input);
            std::cout <<"The word has been added. \n";
        }
    }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	existInDictionary()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

bool existsInDictionary (const std::string &input,
                         const std::vector<std::string> &dict)
{
    auto it = find (dict.begin(), dict.end(), input);
    bool found = it != dict.end();
    return found;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	distAlg()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

int distAlg (std::string one, std::string two)
{
    int a = one.size();
    int b = two.size();
    
    std::vector<std::vector<int> > distCalc;
    std::vector<int> max;
    
    for (int i = 0; i <= a ; ++i)
    {
        max.push_back(i);
    }
    distCalc.push_back(max);
    for (int j = 0; j <= b ; ++j)
    {
        max.clear();
        max.push_back(j);
        std::vector<std::vector<int> >::iterator it = distCalc.end();
        distCalc.insert(it,max);
    }
    // Null characters
    one.insert(0," ");
    two.insert(0," ");
    
    for (int j = 1; j <= b ; ++j )
    {
        std::vector<std::vector<int> >::iterator it = distCalc.begin();
        it += j;
        max.clear();
        max.push_back(j);
        
        for (int i = 1; i <= a; ++i)
        {
            // Using wikipedia definition, first min part of function
            int option1 = max[i-1]+1;            // Deletion
            int option2 = distCalc[j-1][i]+1;    // Insertion
            int option3 = distCalc[j-1][i-1];    // Substitution
            if (one[i] != two[j])                // Indicator function
            {
                option3=distCalc[j-1][i-1]+1;
            }
            int minimum;
            
            // Outputting the options in relation to the if statement
            if (i > 1 && j > 1 && one[i] == two[j-1] && one[i-1] == two[j])
            {
                int option4 = distCalc[j-2][i-2]+1;       // Transposition
                minimum =
                std::min(std::min(std::min
                                  (option1,option2),option3),option4);
            }
            
            // Otherwise part of the function from wikipedia
            if (i == 1 || j == 1 || one[i] != two[j-1] || one[i-1] != two[j])
            {
                minimum =
                std::min(std::min(option1,option2),option3);
            }
            
            max.push_back(minimum);
        }
        distCalc.insert(it,max);
        
    }
    return distCalc[b][a];
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	End of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
