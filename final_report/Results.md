# Results
 [Link to our presentation](https://youtu.be/4PynqfNt8oQ)
## BFS
BFS provides the generalization of the Bacon number that we were looking for. A simple BFS from one actor to another will give us a shortest path, and thus, the number of movies it takes to move from one actor to another. We found that most actors of note had a fairly low number, usually around 5 or less.
### sample runs
![BFS Kevin Bacon to Morgan Freeman](https://imgur.com/NGbFQWw)
![BFS Janet Brandes to Bert Dijkstra](https://imgur.com/LEI27ok)

## Dijkstra's Algorithm
Dijkstra's algorithm was similar to BFS, but with weights based on the movie's rating. It was necessary to take ten minus the rating otherwise the path would take a the longest path it could. Output is the path with heighest average rateing per connection.
### sample runs
![Dijkstra's Kevin Bacon to Morgan Freeman](https://imgur.com/mmor0RR)
![Dijkstra's Janet Brandes to Bert Dijkstra](https://imgur.com/2W2hrsD)

## Brandes' Algorithm
We wanted to use Brandes' algorithm to see if there was a more central actor than Kevin Bacon. There turned out to be tecnical complications as the centrality of an actor quickly jumped as the graph got more connected moving past what a long double can contain. We used a subset containing only movies with a rateing above 4.
### sample run
![Brandes's on rateing above 9](https://imgur.com/wIHt3qP)

