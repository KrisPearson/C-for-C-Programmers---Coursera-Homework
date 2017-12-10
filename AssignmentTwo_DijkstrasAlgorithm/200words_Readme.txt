This is the first time I've had to implement a graph before, and nor studied graphs of this nature or adhecency matrices/list.

I have once before, some time ago, implemented A* pathfinding in a C# script, so it was from this that I drew most inspiration from.
This did lead to some issues, as I attempted to implement my own Heap to sort the search order of Nodes by converting
the C# code. This uses a combination of interfaces and templates ina  way that I failed to emmulate in C++.
That being said, I did gain a greater insight into both, so it was still worthwhile, though it did consume more time than I would have liked.

I found the abstract nature of the more orthodox implementation of graphs to be somewhat intimidating, which is why I opted for the more familiar
class/struct based approach. One could say that this was overkill, but structuring the program like this would enable future expansion of the code, say
by deriving children from the Node class for different functionality. 

The final conclusion I drew from this is that a higher density graph usualy leads to a shorter path.



References Used
===============
Dijkstra's Algorithm - Adjacency Lists
http://www.cplusplus.com/forum/general/124853/

TheHappieCat: How to Do PATHFINDING: Dijkstra's Algorithm
https://www.youtube.com/watch?v=LDCa4U-ZbJ0

Shreyans Sheth: Answer on Quora 
https://www.quora.com/What-is-the-most-simple-efficient-C++-code-for-Dijkstras-shortest-path-algorithm

Erik Hazzard: Dijkstra's Algorithm - Shortest Path
http://vasir.net/blog/game_development/dijkstras_algorithm_shortest_path

Quora: What is the most simple & efficient C++ code for Dijkstra's shortest path algorithm?
https://www.quora.com/What-is-the-most-simple-efficient-C++-code-for-Dijkstras-shortest-path-algorithm