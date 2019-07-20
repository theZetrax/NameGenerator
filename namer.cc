#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random> // google: cpp random class

void selectLine(int iter, std::string *output, std::string namedb);
unsigned genRandomNumber(const int lowerLimit, const int upperLimit);
unsigned count_db(std::string db);
void createOutputFile(std::string *output, std::string outputName);

int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;
    
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distro(1, 12);

    if(argc != 3)
    {
        cout << "usage: namer [nameDatabase] [credentialDatabase]" << endl;
        return 0;
    }
    
    std::string output = "";

    selectLine(genRandomNumber(1, count_db(argv[2])), &output, argv[2]);
    output += " ";
    selectLine(genRandomNumber(1, count_db(argv[1])), &output, argv[1]);
    output += " ";
    selectLine(genRandomNumber(1, count_db(argv[1])), &output, argv[1]);
    
    cout << "Name: " << output << endl;
    createOutputFile(&output, "your_name.txt");
    

    return 0;
}

void selectLine(int iter, std::string *output, std::string db) 
{
    std::ifstream fin;
    std::string line;
    fin.open(db);

    for(int count = 0; count < iter && fin; count++)
    {
        if(line.back() == ',')
            line.clear();
        getline(fin, line);
    }

    (*output) += line;

    if((*output).back() == ',') 
        (*output).pop_back();
    
    fin.close();
}

unsigned genRandomNumber(const int lowerLimit, const int upperLimit) 
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    std::uniform_int_distribution<int> distro(lowerLimit, upperLimit);

    return distro(gen);
}

unsigned count_db(std::string db) 
{
    std::ifstream fin;
    fin.open(db);
    unsigned counter = 0;
    std::string lines;
    
    while(fin)
    {
        getline(fin, lines);
        counter++;
    }

    return counter;
}

void createOutputFile(std::string *output, std::string outputName)
{
    std::ofstream fout;
    fout.open(outputName);

    if(fout.is_open())
    {
        fout << *output;
        std::cout << "Name Generated in file: " << outputName;
        fout.close();
    }
}
