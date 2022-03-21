#include "graph.h"
using std::string;
using std::list;
using std::unordered_map;
using std::vector;
using std::fstream;
using std::stringstream;
using std::ios;
using std::stack;
using std::queue;
using std::priority_queue;
using std::cout;
using std::endl;
using std::pair;

Graph::Graph(string edgesFileName, bool hideTextFlag){
    failedLoad = false;
    string line, entry;
    int count = 0, target = 1;
    fstream edgesFile (edgesFileName, ios::in); 
    if (edgesFile.is_open()){
        while (getline(edgesFile, line)){   //Read in edges
            Connection forward;
            Connection reverse;
            stringstream str(line); //Parse into two connections, one forward one reverse
            getline(str, entry, ',');
            forward.name = entry;
            reverse.destination = entry;
            getline(str, entry, ',');
            forward.destination = entry;
            reverse.name = entry;
            getline(str, entry, ',');
            forward.title = entry;
            reverse.title = entry;
            getline(str, entry);
            forward.rating = std::stof(entry);
            reverse.rating = std::stof(entry);

            addEdge(forward);   //Add both connections
            addEdge(reverse);
            if (!hideTextFlag){
                ++count;
                if (count == target){
                    cout << "Successfully read " << count << " entries in " << edgesFileName << "." << endl;
                    target *= 2;
                }
            }
            
        }
        if (!hideTextFlag){
            cout << "Successfully read all " << count << " entries in " << edgesFileName << "." << endl;
        }
            
    }
    else{
        cout << "Could not read " << edgesFileName << "." << endl;   //Failed to open file
        failedLoad = true;  
    }
    edgesFile.close();
    if (!hideTextFlag){
        cout << "----+====+----" << endl;
    }
}

void Graph::addEdge(Connection c){
    adjLists[c.name].push_back(c);  //Add connection to edge list of that name
}

int Graph::size(){
    return adjLists.size();
}

vector<Graph::Connection> Graph::BFS(string start, string target) const{
    vector<Connection> output;

    if (adjLists.count(start) == 0){ //Start doesn't exist in graph
        output.push_back(Connection(start, "", "", -2.0));
        return output;
    } else if (adjLists.count(target) == 0){    //Target doesn't exist in graph
        output.push_back(Connection(target, "", "", -3.0));
        return output;
    } else if (start == target){       //Start and target are same
        output.push_back(Connection(start, start, "(Any movie starring " + start + ")", -1.0));
        return output;
    }

    unordered_map<string, bool> visited;
    stack<Connection> path;
    queue<Connection> q;

    visited[start] = true;

    for (auto& i : adjLists.at(start)){ //Run through depth 1 manually because of Connection structure
        string nextActor = i.destination;
        if (nextActor == target){
            output.push_back(i);
            return output;
        }
        q.push(i);
        visited[i.destination] = true;
    }

    while (!q.empty()){ //Repeat until searched entire connected component
        Connection currentConnection = q.front();
        q.pop();
        path.push(currentConnection);   //Take step along output path
        bool foundNewActor = false;
        for (const auto& i : adjLists.at(currentConnection.destination)){
            string nextActor = i.destination;
            if (nextActor == target){       //Create output vector from path
                path.push(i);
                while(!path.empty()){
                    if (output.empty() || output.back().name == path.top().destination){    //Filter out fragmented branches of path
                        output.push_back(path.top());
                    }
                    path.pop();
                }
                std::reverse(output.begin(), output.end());
                return output;
            } else if (!visited[nextActor]){   //If found a new actor
                foundNewActor = true;
                visited[nextActor] = true;
                q.push(i);
            }
        }
        if (!foundNewActor){    //Step back along path if dead end
            path.pop();
        }
    }
    return vector<Connection>();    //No path found
}

vector<Graph::Connection> Graph::dijkstras(string start, string target) const{
    
    unordered_map<string, float> distances;
    unordered_map<string, bool> visited;
    unordered_map<string, Connection> previous;
    struct Comparator{  //Greater than comparator for priority queue
        int operator() (const Graph::Connection& c1, const Connection& c2){
            return 10-c1.rating > 10-c2.rating;
        }
    };
    priority_queue<Connection, vector<Connection>,Comparator> q;
    vector<Connection> output;

    if (adjLists.count(start) == 0){ //If target doesn't exist
        output.push_back(Connection(start, "", "", -2.0));
        return output;
    } else if (adjLists.count(target) == 0){
        output.push_back(Connection(target, "", "", -3.0));
        return output;
    } else if (start == target){   //If start is target
        output.push_back(Connection(start, start, "(Any movie starring " + start + ")", -1.0));
        return output;
    }

    for (const auto& e : adjLists){ //Set all distances to infinity
        if (!e.second.empty()){
            distances[e.second.front().name] = __FLT_MAX__;
        }
    }

    distances[start] = 0;   //Distnace to itself is 0
    visited[start] = true;

    for (const Connection& i : adjLists.at(start)){ //Calculate depth 1 mantually due to connection structure
        q.push(i);
        distances[i.destination] = (10.0 - i.rating);
        previous[i.destination] = i;
    }
    Connection currentConnection;
    while (! q.empty() && q.top().destination != target){
        currentConnection = q.top();
        q.pop();
        for (const Connection& i : adjLists.at(currentConnection.destination)){
            if (!visited[i.destination] && distances[i.destination] > distances[i.name] + 10-i.rating){ 
                distances[i.destination] = distances[i.name] + 10-i.rating; //If found a new shorted path, update distance and previous
                previous[i.destination] = i;
                q.push(i);
            }
        }
        visited[currentConnection.destination] = true;
        if (q.empty()){
            return vector<Connection>(); //No path found
        }
    }
    currentConnection = q.top();
    while(previous.count(currentConnection.name) > 0){  //Walk back along previous path to get output
        output.push_back(currentConnection);
        currentConnection = previous[currentConnection.name];
    }
    output.push_back(currentConnection);
    std::reverse(output.begin(), output.end());
    return output;
}

pair<string, long double> Graph::brandes() const {
    unordered_map<string, long double> betweenness;
    for (const auto& pair : adjLists) {
        string actor = pair.first;
        stack<string> s;
        //list of all nodes imediately processing the input
        unordered_map<string, list<string>> predecessor;
        unordered_map<string, size_t> num_paths;
        num_paths[actor] = 1; //only one shortest path to yourself
        unordered_map<string, size_t> distances;
        distances[actor] = 0; //distance to yourself is 0

        queue<string> q;
        q.push(actor);
        while (!q.empty()) {
            string current_actor = q.front();
            q.pop();
            s.push(current_actor);

            size_t& current_distance = distances.at(current_actor);
            for (const Connection& connection : adjLists.at(current_actor)) {
                predecessor[connection.destination].push_back(current_actor);
                //if desination is unvisited
                if (distances.find(connection.destination) == distances.end()) {
                    distances[connection.destination] = current_distance + 1;
                    q.push(connection.destination);
                    num_paths[connection.destination]++;
                //new shortest path from current_actor to destination
                } else if (distances[connection.destination] ==
                           current_distance + 1) {
                    num_paths[connection.destination] +=
                        num_paths[current_actor];
                }
            }
        }

        unordered_map<string, long double> dependency;
        while (!s.empty()) {
            for (const string& prev_actor : predecessor[s.top()]) {
                dependency[prev_actor] += 
                    (static_cast<long double>(num_paths[prev_actor])
                     / static_cast<long double>(num_paths[s.top()])) *
                    (1.0 + dependency[s.top()]);
            }

            if (s.top() != actor) {
                betweenness[s.top()] += dependency[s.top()];
            }
            s.pop();
        }
    }

    //find max betweeness
    std::pair<string, long double> max = {"", 0};
    for (const std::pair<string, long double>& pair : betweenness) {
        if (pair.second > max.second) {
            max = pair;
        }
    }

    return max;
}