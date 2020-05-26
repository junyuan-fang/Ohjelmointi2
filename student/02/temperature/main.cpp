#include <iostream>
#include <string>

using namespace std;

int main()
{
    int temp;
    cout << "Enter a temperature: ";
    cin>>temp;
    float fahrenheit= temp*1.8+32;
    float celsius=(temp-32)/1.8;
    cout << temp<<" degrees Celsius is "<<fahrenheit<<" degrees Fahrenheit"<<endl;
    cout << temp<<" degrees Farenheit is "<<celsius<<" degrees Celsius"<<endl;
    return 0;
}
