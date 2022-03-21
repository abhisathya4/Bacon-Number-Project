#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <unordered_set>

using std::string;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::vector;

/**
 * @brief converts a file from tsv to csv
 * 
 * @param tsv file in tsv format
 * @param csv file in csv format
 */
void tsvcsv(ifstream& tsv, ofstream& csv) {
    string line;
    while (getline(tsv, line)) {
        std::replace(line.begin(), line.end(), '\t', ',');
        csv << line << endl;
    }
}

/**
 * @brief takes an ifstream and continues until a new movie is found
 * 
 * @param i  //input file
 * @param line //the line that the file is currently on
 * @param comma_position //the position of the deleminator for the movie id
 */
void continueToNextTitle(ifstream& i, string& line, int comma_position) {
    string current_movie = line.substr(0, comma_position);
    while (!i.eof()) {
        getline(i, line);
        if (line.substr(0, comma_position) != current_movie) { //if 1 was found
            return;
        }
    }
}

/**
 * @brief test if substring is in string
 * 
 * @param string the string to search in
 * @param substring the string to search for
 * @return true if substring is found
 * @return false if substring is not found
 */
inline bool stringContains(const std::string& string, const std::string& substring) {
    return (string.find(substring) != string::npos);
}

/**
 * @brief selects a movie title for every movie id. prefers the US title or th
 *        first line if US title is not available.
 * 
 * @param input input csv file
 * @param output output csv file
 */
void csvTitleTrim(ifstream& input, ofstream& output) {
    string line;
    getline(input, line);  //remove collumn titles
    output << line << endl;     //add collumn titles to output

    string first_title_line;
    getline(input, first_title_line); 

    int first_comma_position = first_title_line.find(',');
    string current_movie = first_title_line.substr(0, first_comma_position);
    while (getline(input, line)) {
        //detect if we did not find a US title
        if (line.substr(0, first_comma_position) != current_movie) {
            output << first_title_line << endl;
            first_title_line = line;
            current_movie = line.substr(0, first_comma_position);
            continue;
        } else if (stringContains(line, ",US,")) { //prefer a US title
            output << line << endl;
            continueToNextTitle(input, line, first_comma_position);
            first_title_line = line;
            current_movie = line.substr(0, first_comma_position);
            continue;
        }
    }
}

/**
 * @brief selects only actors and actresses from the pricipals file
 * 
 * @param input 
 * @param output 
 */
void csvPrincipleTrim(ifstream& input, ofstream& output) {
    string line;
    getline(input, line);  //remove collumn titles
    output << line << endl;     //adds collumn titles to output

    while (getline(input, line)) {
        if (stringContains(line, "actor") || stringContains(line, "actress")) {
            output << line << endl;
        }
    }
}

/**
 * @brief prints out all combinations of shared actors for a movie
 * 
 * @param output the ofstream to output to
 * @param shared_actors the actors that share movie_title
 * @param rateing the rateing for the movie
 * @param movie_title the title for the movie
 */
void outputSharedActors(ofstream& output,
                        const vector<string>& shared_actors,
                        const string& rateing,
                        const string& movie_title) {
    for (size_t i = 0; i < shared_actors.size(); ++i) {
        for (size_t j = i + 1; j < shared_actors.size(); ++j) {
            output << 
            shared_actors[i] << ',' <<
            shared_actors[j] << ',' <<
            movie_title << ',' <<
            rateing << endl;
        }
    }
}

/**
 * @brief gets a vector of strings that represents the row and each entry is a
 *          collumn
 * 
 * @param line the line to convert to a vector
 * @return vector<string> each word delimated by a ','
 */
vector<string> getRow(string line) {
        vector<string> row;
        std::stringstream ss(line);
        string word;
        while (getline(ss, word, ',')) {
            row.push_back(word);
        }

        return row;
}

/**
 * @brief skips empty rows of an ifstream
 * 
 * @param input ifstream to skip empty rows for
 * @param line the current line that the ifstream was on
 */
void skipEmptyRows(ifstream& input, string& line) {
    while (line == "") {
        getline(input, line);
    }
}

/**
 * @brief Get the Shared Actors from the movie that the current ifstream is on.
 *          ifstream has already read the first line and that is in line.
 * 
 * @param input ifstream to read movie from.
 * @param line the first line to read
 * @return vector<string> the actors that share a movie
 */
vector<string> getSharedActors(ifstream& input, string& line) {
    skipEmptyRows(input, line);

    vector<string> row = getRow(line);
    string current_movie = row[1];
    vector<string> shared_actors; 

    shared_actors.push_back(row[0]);

    while (getline(input, line)) {
        skipEmptyRows(input, line);
        row = getRow(line);
        if (row[1] != current_movie) break;
        shared_actors.push_back(row[0]);
    }

    return shared_actors;
}

/**
 * @brief Create a Edge File csv from a file containing titles on the first line
 *          and contents containing, in this order:
 *          actor_name,movie_title,rateing.
 * 
 * @param input a stream with the the above formate 
 * @param output a stream that shows actors who star in a movie together
 *                  format is as such: 
 *                  actor_name1,actor_name2,movie_title,rateing 
 */
void createEdgeFile(ifstream& input, ofstream& output) {
    string line;
    getline(input, line); //remove collumn titles

    getline(input, line);
    while (!input.eof()) {
        vector<string> row = getRow(line);
        string movie = row[1];
        string rateing = row[2];

        outputSharedActors(output, 
                           getSharedActors(input, line),
                           rateing,
                           movie);       
    }
}

/**
 * @brief Create a file of Nodes that are in the Graph. Only Nodes that are
 *          connected to one other node is included.
 * 
 * @param input 
 * @param output 
 */
void createNodeFile(ifstream& input, ofstream& output) {
    std::unordered_set<string> actor_set;
    string line;
    getline(input, line); //remove collumn titles

    getline(input, line);
    while(!input.eof()) {
        vector<string> shared_actors = getSharedActors(input, line);
        if (shared_actors.size() > 1) { //actor must be paired with > 1 actor
            for (const string& actor : shared_actors) {
                if (actor_set.find(actor) == actor_set.end()) {
                    actor_set.insert(actor);
                    output << actor << endl;
                }
            }
        }
    }
}