
# Leading Question:
There is a popular idea in the film industry of the "Bacon Number", which is the shortest connected path from an actor to Kevin Bacon, where each connected step along that path signifies two actors costarring in a movie.  We want to generalize this idea to work between any two given actors as endpoints of the path, as well as see  if the most connected person truly is Kevin Bacon, or if there is a better choice for the most central person in Hollywood. We also want to see what effect weighting the movies based on their rating would have.
We envision 2 major final deliverables:

1) To be able to input any two actors names and get back the shortest connected path between them, either using rating-weighted edges or not  
2) To be able to see who the most centrally connected person in the dataset is

# Dataset Acquisition and Processing:
For our dataset, we will be using the IMDB database found at [https://www.imdb.com/interfaces/](https://www.imdb.com/interfaces/).  We will use only actors from this dataset as part of our graph.  This dataset includes a lot of excess information we do not intend to use, such as non-actor roles, dates, runtime, and others.  Thus, we will need to preprocess the data using Microsoft Access to reduce the scope and format to be what we want..  Each actor is also stored with a unique identifier rather than a name, so we will need to replace each identifier with the actual name it represents.  
  
After preprocessing, our data will be stored in this format:

**nodes.csv** - List of actor names, 1 per line
``` 
John Smith
Jane Doe
Sarah James
Jessica Adams
Tina Davis
Tommy Thomas
```
**edges.csv** - List of connections, 1 per line (actor1,actor2,rating[1-10],movie title)
```
John Smith,Jane Doe,7.0,Titanic
Sarah James,Tommy Thomas,3.2,Jaws
Tina Davis,Jane Doe,8.5,Star Wars
Tommy Thomas,Jessica Adams,2.8,Star Trek
Tina Davis,Sarah James,5.9,Mission Impossible
```
Notes:  
If an IMDB entry is missing any of this required information, we will not include it in our graph.  
The movie title is listed last sequentially so that commas in the movie title will not have an effect on the comma-separated list

# Graph Algorithms:
#### **Breadth First Traversal**  
This will be the algorithm we use to find the shortest path from one actor to another.  We will start at the first actor and halt the traversal once the second actor is found.

> **Input**: Actor1, Actor2  
**Output**: The unweighted shortest path between them as a list of movies  
**Big-O**: O(n + m) in the worst case, since the two actors could be on opposite sides of the graph and the entire graph would need to be traversed

#### **Dijkstra's Shortest Path Algorithm (Covered)**  
We will use this algorithm to find the shortest weighted path between any two actors, using the rating of each movie as the weight for that edge, with higher ratings corresponding to lower weights (using 10-rating as the weight).  For actors that worked together on multiple movies, we will use the highest rated from among movies they worked on, which would lead to the least weight along that connection.

> **Input**: Actor1, Actor2  
**Output**: The weighed shortest path between them as a list of movies with their ratings  
**Big-O**: O(n + mlog(n)) since we plan to use the original min-priority queue implementation.

#### **Brandes' Betweenness Centrality Algorithm (Uncovered)**  
We will use this algorithm to find the centrality of every actor in the dataset.  From there, we can find the most central actor to see if Kevin Bacon is really the most connected person in Hollywood, or if there is a better choice.

> **Input**: None  
**Output**: The centrality of each actor, which we will then use to find the most central actor  
**Big-O**: O(nm) since since our graph is unweighted and sparse (m << n<sup>2</sup>).

# Timeline:
- Week 1
	- Process Data
		- Remove non actors
		- Replace UUIDs with names
		- Format into lists of nodes and edges
  - Create graph structure and basic functionality
- Week 2
	- Breadth First Search
	- Overflow from Week 1 (since there is still an MP in progress)
- Week 3
	- Dijkstra's Shortest Path Algorithm
	- Implement command line interface for inputs / outputs
- Week 4
	- Mid-project check-in
	- Brandes' Betweenness Centrality Algorithm
- Week 5
	- Finish written report
	- Buffer time in case anything takes longer than expected
 