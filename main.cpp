#include <iostream>
#include "graph.h"

using std::cout;
using std::cin;
using std::getline;
using std::string;
using std::endl;

int main(int argc, char* argv[]){
    string edgeFile, choice;
    bool running = true;
    if (argc < 2){
        cout << "Please enter edges file name:";
        getline(cin,edgeFile);
    }
    else{
        edgeFile = argv[1];
    }

    Graph imdb(edgeFile, false);
        
    while (imdb.failedLoad){
        cout << "Failed to load edge file.  Please ensure that the file name is spelled properly (including the .csv) and that its contents are properly formatted." << endl;
        cout << "Please enter edges file name:";
        getline(cin,edgeFile);
        imdb = Graph(edgeFile, false);
    }
    
    while (running){
        cout << "Please select an option from this list by entering the corresponding number \n 0 -> Exit\n 1 -> BFS\n 2 -> Dijkstra's\n 3 -> Brandes'\nSelection: ";
        cin >> choice;
        while (!(choice == "0" || choice == "1" || choice == "2" || choice == "3")){
            cout << "Please select valid option\nSleection: ";
            cin >> choice;
        }
        switch (std::stoi(choice)){
            case 0:
                return 0;
                break;
            case 1:{
                cout << "Please enter an actor (exactly how they appear in the edges file): ";
                cin.ignore();
                string start, target;
                getline(cin,start);
                cout << "Please enter another actor: ";
                getline(cin,target);
                auto path = imdb.BFS(start, target);
                cout << "----+====+=----" << endl;
                if (path.empty()){
                    cout << "No path between the two actors was found.\n----+====+=----" << endl;
                }
                else if (path[0].rating < 0){
                    cout << path[0].name << " does not exist in the graph.\n----+====+=----" << endl;
                }
                else{

                    for (auto c : path){
                        cout << c.name << " was in \"" << c.title << "\" with " << c.destination << "." << endl;
                    }
                    cout << "There are " << (path.size() == -1.0 ? 0 : path.size()) << " degrees of separation between " << start << " and " << target << ".\n----+====+=----" << endl;
                }
                break;
            }
            case 2:{
                string start, target;
                cout << "Please enter an actor (exactly how they appear in the edges file): ";
                cin.ignore();
                getline(cin,start);
                cout << "Please enter another actor: ";
                getline(cin,target);
                auto path = imdb.dijkstras(start, target);
                cout << "----+====+=----" << endl;
                if (path.empty()){
                    cout << "No path between the two actors was found.\n----+====+=----" << endl;
                }
                else if (path[0].rating < 0){
                    cout << path[0].name << " does not exist in the graph.\n----+====+=----" << endl;
                }
                else{
                    float sum = 0.0;
                    for (auto c : path){
                        cout << c.name << " was in \"" << c.title << "\" (rated " << c.rating << ") with " << c.destination << "." << endl;
                        sum += c.rating;
                    }
                    cout << "The path between " << start << " and " << target << " has a rating of " << sum << ".\n----+====+=----" << endl;
                }
                break;
            }
            case 3:{
                std::pair<string, float> output = imdb.brandes();
                cout << "The most central node of the graph is " << output.first << " with a centrality of " << output.second << ".\n----+====+=----" << endl;

            }
        }
        cout << "Would you like to run another algorithm? (y/n): ";
        cin >> choice;
        while (!(choice == "y" || choice == "Y" || choice == "n" || choice == "N")){
            cout << "Please enter y or n: ";
            cin >> choice;
        }
        if (choice == "n" || choice == "N"){
            running = false;
        }
    }
    
    return 0;
}