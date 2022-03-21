# The Bacon Number

### Where is everything located

1. The main code functions are all located in *graph.cpp* and *graph.h*
2. Our user interface is located in *main.cpp*
3. Our code to preprocess the data is located in the *preprocess* folder
4. Our test cases are all located in the *tests* folder
5. Our complete, preprocessed dataset is located [here](https://drive.google.com/drive/folders/1YBTJUh0QvroLMluP6hYEMtOgIvG7y0Ar?usp=sharing), as it is too large of a file size for GitHub to host, since it contains ~6.6 million entries.  To use it, it should be placed in the main project folder.
6. Our development log, results, and goals are located in the *final_report*
7. Our presentation video is located in the *results.md* file

### How to use our algorithms:
#### User Input
First, run *make* to compile the program.
Then, run either *./imdb* or *./imdb [filename].csv*
If run without a provided filename, it will prompt the user for a filename.  Note that this filename should have the .csv extension, and that the file should be placed in the main project folder.
If run with a provided filename, it will automatically load that file as though the user had input it in runtime.
Each line of the input file should be of the format (Do not put spaces after the commas):
```
Actor1,Actor2,MovieTitle1,Rating1[1.0-10.0]
```
For example
``` 
John Smith,Jane Doe,Titanic,7.0
Sarah James,Tommy Thomas,Jaws,3.2
Tina Davis,Jane Doe,Star Wars,8.5
Tommy Thomas,Jessica Adams,Star Trek,2.8
Tina Davis,Sarah James,Mission Impossible,5.9
```
The interface will then prompt the user to choose an algorithm by entering its corresponding number (1 = BFS, 2 = Dijkstra's, 3 = Brandes') or 0 to exit.
For BFS and Dijkstra's, it will prompt the user to enter two actors, one after the other, exactly how they appear in the input file.
It should look something like this:
```
Please select an option from this list by entering the corresponding number
 0 -> Exit
 1 -> BFS
 2 -> Dijkstra's
 3 -> Brandes'
Selection: 1
Please enter an actor (exactly how they appear in the edges file): John Smith
Please enter another actor: Jane Doe
```
The results will then be displayed to the terminal, where it will then prompt the user if they would like to run another algorithm

**Note:** Our database include actors with names containing characters that do not display properly in the terminal.  We have chosen to keep these actors in our graph, as they represent important connections, but as a result, some outputs may contain strange characters.

For Brandes', no user input is needed, and the user will simply need to select the 3rd option from the main list and it will output the result.
#### Test cases
First run *make test* to compile the tests.
Then, run *./test* to run the full catch testing suite.

Our tests cover all three algorithms.  For BFS, we tested various graphs and nodes in them to see if the paths they returned matched the expected output.  For Dijkstra's, we tested various graphs and nodes to see if they returned the proper path and the proper weight of that path.  For Brandes', we calculated the results of small graphs by hand and then checked to make sure that the outputs matched out calculated most central nodes.
