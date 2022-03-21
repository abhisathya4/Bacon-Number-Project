# DEVELOPMENT
#### This document was originally a weekly updated Google Doc, since the original prompt only said that git commits were "strongly encouraged".  After our mid-project check-in, our mentor suggested we switch to git commits, so we did.  Also, it seems that renaming the file to DEVELOPMENT.MD may have removed some of the commit history.

## Week of Nov 8
--All worked on proposal, contract, and project plan--
 - Nash: wrote up the initial proposal (sorry for the formatting). 
 - Abhi: Worked on discussing specifics of graph structure during the contract writing meeting.
 - Arnab: I helped with a proposal and a contract.
 - Justin:  Our initial proposal had a few things missing and some formatting errors, so I went through and fixed what needed to be fixed for the initial proposal

## Week of Nov 15
 - Nash: fiddled with access, mostly unsuccessfully. Getting WSL on my machine for longer/faster dataset calculations. 
 - Abhi: Figured out how to implement the graph, using the adjacency list implementation. Wrote the skeleton for the entire require graph functionality. Code was able to build the adjacency list and connections vector but lacked the linkages in between. Implementation had a bug relating to the first connection for an actor not displaying correctly.
 - Arnab: Helped with graph structure and implementation, as well as started debugging.
 - Justin:  For BFS, I wrote the generalizable structure while waiting for information about exactly how the graph will be implemented/interfaced.

## Week of Nov 22
--We all took this week off for Thanksgiving break--

## Week of Nov 29
 - Nash: wrote a tsv to csv converter. Discovered that access limits database files to 2 GB, so wrote a trim function for the principals csv, and title csv. Principal trim removes non-actors. titleTrim selects a title from different localizations, taking US or the first title if no US name. 
 - Abhi: Fixed functionality relating to maintaining the graph structure. Fixed bugs in reading in of the files, building the vector of connections while updating double iterators in adjacency list and actor struct. Added some documentation. However got a segfault at updateActorPointer() invalid write  of size 8. 
 - Arnab: Helped debug the program to create the graph necessary.
 - Justin:  For BFS, with the structure of the graph known, I updated it with the proper iterator interface, though it still remains untested due to a bug in the main graph code

## Week of Dec 6
 - Justin: Rewrote some of the main graph structure and BFS, started on Dijkstra's
 - Arnab: Assisted with debugging and restructuring of graph and layout, and started on presentation.
 - Abhi: Tried to fix main graph structure. Wrote the testsuite for completed functionality, including the makefile and test data files.
 - Nash: preprocessing for database finishing up with various bugs fixed.

## Week of Dec 13
 - Justin: Completed Dijkstras, fixed some bugs in BFS, completed command line interface
 - Arnab: Focused on building a presentation and report.
 - Abhi:
 - Nash: Compleated Brandes's Algorith. Wrote Final Report. Some bugs fixed in tests
