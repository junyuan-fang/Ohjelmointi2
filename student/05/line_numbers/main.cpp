#include <iostream>
#include <fstream>

using namespace std;

void get_name( string* target){
    cin>>* target;
    string line_feed="";
    getline(cin,line_feed);
}


int main()
{
    string in_file_name="";
    cout<<"Input file: ";
    get_name(&in_file_name);

    string out_file_name="";
    cout<<"Output file: ";
    get_name(&out_file_name);

    ifstream infile_var(in_file_name);
    if (! infile_var){
        cout<<"Error! The file not_a_file.input cannot be opened."<<endl;
        return EXIT_FAILURE;
    }
    else{
        ofstream outfile_var(out_file_name);
        string rivi;
        int i=1;
        while(getline(infile_var,rivi)){
            outfile_var<<i<<" "<<rivi<<endl;
            ++i;
        }
        outfile_var.close();

    }
    infile_var.close();

}
