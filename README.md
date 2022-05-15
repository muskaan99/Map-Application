# Map-Application

# Introduction
The project focuses on using data structures in C++ and implementing various graph algorithms to build a map application for the area around University of Southern California. Made use of OpenCV for visualizations of the map.

For the full report refer [Report.md](https://github.com/muskaan99/Map-Application/blob/main/REPORT.md)



# Tasks performed

Performed the following tasks:

i) Autocomplete the location name:  Implemented a method to type the partial name of a location and return a list of possible locations with partial name as prefix

ii) Coordinates: Finds the latitude and longitude of the location entered by the user

iii) Shortest Path: Calculates shortest path between two places entered by the user

iv) Travelling Salesman: Finds the shortest route that covers all the locations exactly once and goes back to the start point.(Used Brute Force, Early Backtracking and 2-opt Heuristic)

v) Cycle Detection: Determining whether a cycle exists in the square shaped subgraph or not

vi) Topological Sort: Given a vector of location names and dependencies between the locations, the function provides a visualization on the map demonstrating a feasible route.

vii) Find Nearby: Given attribute name C, a location name L and a number r and k, finds at most k locations in attribute C on the map near L (L not included) with the range of r and return a vector of string ids. The order of locaitons should from nearest to farthest. 

# Learnings

* Understanding the importance of optimization techniques, such as memoization and backtracking, and their heuristics in real world applications when you have large amounts of data
* Relation of the genetic algorithm, which is based on the principal of evolution and survival of the fittest to travelling salesman implementation
* Efficiently being able to access and handle data using STLs
* Importance of the role of testing to not only test your code, but to be able to catch corner case bugs.

# Conclusion

We have implemented the Trojan Map application as a guide to navigate through USC and its surrounding areas. We learnt and used many diverse algorithms in the project ranging from shortest path algorithms (such as Dijkstra and Bellman-Ford) to TSP implementations (such as Backtracking and Genetic Algo) and edit distance calculations. We were able to get an insight into how Google Maps functions from within and aim to implement an extension of our project to the entire LA county. 
