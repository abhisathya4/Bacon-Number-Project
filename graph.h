#pragma once

#include <string>
#include <list>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <utility>

class Graph{
    public:
        struct Connection {
            Connection(std::string nameInput, std::string destinationInput, std::string titleInput, float ratingInput) 
                : name(nameInput), destination(destinationInput), title(titleInput), rating(ratingInput) {
            }
            Connection() = default;
            bool operator==(const Connection & rhs) const {
                if (this->name == rhs.name && this->destination == rhs.destination
                    && this->rating == rhs.rating && this->title == rhs.title) {
                        return true;
                }
                return false;
            }
            std::string name;
            std::string destination;
            std::string title;
            float rating;
        };
        Graph(std::string edgessFileName, bool hideTextFlag = true);
        int size();
        std::vector<Connection> BFS(std::string start, std::string target) const;
        std::vector<Connection> dijkstras(std::string start, std::string target) const;
        std::pair<std::string, long double> brandes() const;
        bool failedLoad;
        std::unordered_map<std::string, std::list<Connection>> get_unordered_map() {
            return adjLists;
        }
    private:  
        std::unordered_map<std::string, std::list<Connection>> adjLists;
        void addEdge(Connection c); 
};

