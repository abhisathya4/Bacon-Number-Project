#include <iostream>

#include "preprocess.cpp"

using std::cout;
using std::endl;

int main(int argc, char * argv[]) {
    if (argc < 4) {
        cout << "please input \"./<file_name> <input filepath> <output filepath> <operation>" << endl;
        cout << "operations are as such:" << endl;
        cout << "   0: tsvcsv. convert from tsv format to csv format" << endl;
        cout << "   1: csvTitleTrim. selects a title for each movie ";
        cout <<         "from the imbd titles file" << endl;
        cout << "   2: csvPrincipleTrim. selects all actors and actresses ";
        cout <<         "from the imdb titles file" << endl;
        cout << "   3: createEdgeFile. create the edge file from a properly ";
        cout <<         "formated csv." << endl;
        cout << "   4: createNodeFile. create a file listing all actors in ";
        cout <<         "the graph." << endl; 
        return 1;
    }
    
    ifstream input;
    ofstream output;
    input.open(argv[1]);
    output.open(argv[2]);

    if (!input.is_open()) {
        cout << "cannot open input file" << endl;
        return 1;
    }

    switch (atoi(argv[3])) {
        case 0:
            tsvcsv(input, output);
            break;
        case 1:
            csvTitleTrim(input, output);
            break;
        case 2:
            csvPrincipleTrim(input, output);
            break;
        case 3:
            createEdgeFile(input, output);
            break;
        case 4:
            createNodeFile(input, output);
            break;
        default:
            cout << "not a valid operations" << endl;
    }

    input.close();
    output.close();
}