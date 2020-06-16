#include <iostream>
#include <string>
#include <algorithm>
#include <random>
using namespace std;
string:: iterator iteraattori( string& txt, const string& operaattori ){
    string ::size_type pituus=txt.length();
    if (pituus<=2){
        return txt.begin();
    }
    if (operaattori=="+"){
        return txt.begin()+1;
    }
    else if (operaattori=="-"){
        return txt.begin()+pituus-2;
    }
    return txt.begin();//nerver will be reached
}
int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;

    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }

        else{
            string:: iterator beginning;
            beginning=iteraattori(word, "+");
            string:: iterator ending;
            ending =iteraattori(word, "-");
            shuffle(beginning, ending,generator);
        }
	
        std::cout << word << std::endl;
    }
}
