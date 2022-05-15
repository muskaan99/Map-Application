# TEAM MEMBERS

1. Muskaan Parmar (USC ID: 1660937440)
2. Nisha Elizabeth Jacob (USC ID: 8915179886)

# Design Overview

* Our design uses structures and helper functions to try and solve various shortest path algorithms and the travelling salesman problem with heuristics. 
* To compute the shortest path, we have used the Dijkstra and Bellman Ford algorithms and compared it with BFS to show the optimization in path length.
* We have utilised the traditional brute-force method and early backtracking to implement the Travelling Trojan algorithm.
* We have also used two other heuristic methods, which give 'good enough' values but are extremely faster in execution - 2-opt and Genetic Algorithm.


# Detailed explanation of functions

## **_1. Autocomplete_**

`std::vector<std::string> TrojanMap::Autocomplete(std::string name)`

* **Input:** User enters a string
* **Output:** Returns a list of all names prefixed by the user input, else, return empty list

* The input string is converted to lower case and spaces are eliminated
*  We loop through all the elements of the map 'data' and compare Node name with the input string
*  If the length of input string is greater than Node name, then that Node is not considered
*  Else, the input string is compared with the substring of Node name and substring is of input string length
*  If a match is found, add Node name to final list

_Time Complexity:_ O(n), where n is the number of nodes

_Time taken to execute:_ 5ms

![image](https://user-images.githubusercontent.com/97588998/166077370-38ef544f-d725-4d12-b485-744ccf5a3e0c.png)

## **_2. GetPosition_**

`std::pair<double, double> TrojanMap::GetPosition(std::string name)`

* **Input:** User enters a string
* **Output:** Returns the latitude and longitude of the place entered by user. If place doesn't exist return (-1,-1)

*  We loop through all the elements of the map 'data' and compare Node name with the input string
*  If the input string and Node name are equal, return Node's latitude and longitude

_Time Complexity:_ O(n), where n is the number of nodes

_Time taken to execute:_ 1ms

![image](https://user-images.githubusercontent.com/97650586/165833180-2c59a410-6c03-4f74-831f-0f05345d1677.png)


## **_3. CalculateEditDistance_**

`int TrojanMap::CalculateEditDistance(std::string a, std::string b)`

* **Input:** User enters two strings
* **Output:** Returns the edit distance between the two input strings
*  Create a 2D vector 'memo' of size len(a)+1 x len(b)+1
*  Initialize base cases:
    - Edit distance between empty strings is zero
    - Edit distance between an empty string and a non-empty string would be the length of the non-empty string
*  Loop through the length of each string. Let D[i][j] be the edit distance between the first i characters of string a and first j characters of string b
*  If a[i] == b[j], D[i][j] = 1+min(D[i-1][j], D[i][j-1], D[i-1][j-1]-1)
*  Else, D[i][j] = 1+min(D[i-1][j], D[i][j-1], D[i-1][j-1])
*  Dynamic programming and memoization is used to reduce execution time.

_Time Complexity:_ O(n<sup>2</sup>), where n is the number of nodes

_Time taken to execute:_ 1ms


## **_4. FindClosestName_**

`std::string TrojanMap::FindClosestName(std::string name)`

* **Input:** User enters a string
* **Output:** Returns a string with smallest edit distance

*  Initialize 'min distance' as INT_MAX
*  We loop through all the elements of the map 'data' and call CalculateEditDistance, passing Node name each time
*  If edit distance is less than 'min distance', update 'min distance' and store Node name
*  Return Node name whose edit distance is minimum

_Time Complexity:_ O(n), where n is the number of nodes

_Time taken to execute:_ 1ms


![image](https://user-images.githubusercontent.com/97650586/165833375-fb5507eb-ab05-41a2-bea5-35215537fa8b.png)


## **_5. CalculateShortestPath_Dijkstra_**

`std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(std::string location1_name, 
                                                                    std::string location2_name)`

* **Input:** User enters two location names
* **Output:** Returns a vector with shortest path

*  Initialize distance to each node as DBL_MAX
*  If user enters invalid location name then empty vector is returned
*  Update the distance of the starting node to 0
*  Create a priority queue to obtain the minimum distance neighbour for each node
*  Push the starting node into the queue
*  Run the below steps till the queue is empty:
*  Get the top most element of the queue, if this is equal to the destination location, break from the loop
*  Mark this node as visited
*  Loop through the node's neighbours. If its current distance > predecessor distance+ edge distance, then update the node's distance
*  Push this node in the queue
*  After the second location is obtained, reverse the path vector and return the path

_Time Complexity:_ O(nlogn), where n is the number of nodes

_Time taken for completion:_ 34 ms

![image](https://user-images.githubusercontent.com/97650586/165833863-f0a5fb08-9558-44a9-af5e-edae7a1ed091.png)


## **_6. CalculateShortestPath_BellmanFord_**

`std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(std::string location1_name, 
                                                                        std::string location2_name)`

* **Input:** User enters two location names
* **Output:** Returns a vector with shortest path

*  Initialize distance to each node as DBL_MAX
*  If user enters invalid location name then empty vector is returned
*  Update the distance of the starting node to 0
*  Run a loop to go through all (n-1) edges
*  Run another loop to go through all the nodes
*  Loop through the node's neighbours. If its current distance > predecessor distance+ edge distance, then update the node's distance
*  If no distances are updated for an iteration, break from the loops
*  Reverse the path vector and return the path

_Time Complexity:_ O(mn), where m is the number of edges and n is the number of nodes

_Time taken for completion:_ 5.17 s


![image](https://user-images.githubusercontent.com/97650586/165834076-06b95487-6bb8-42b7-9a7d-a813c19fd5e1.png)

![image](https://user-images.githubusercontent.com/97650586/165834186-9e3b4c67-59de-43fd-8131-d60f2d3dade6.png)


Bellman Ford takes more time as compared to the Dijkstra Algorithm because we try to find the shortest path using all possible combinations of edges whereas in Dijkstra, we find the unvisited node with shortest distance using only visited nodes. Due to this, Bellman Ford can handle negative cycles whereas Dijkstra is unable to do so.



## **_7. CycleDetection_**

`bool TrojanMap::CycleDetection(std::vector<std::string> &subgraph, 
                                std::vector<double> &square)`

* **Input:** List of location ids within the square vertices defined by the user
* **Output:** Returns whether a cycle exists in the square or not

*  Loop through each location id in the subgraph
*  Mark this node as visited
*  Loop through the node's neighbours, if the node is not located within the square, skip it
*  Keep calling the function recursively till we reach a node, whose neighbour has already been visited and is different from its predecessor node
*  If this is the case, cycle exists within the square and we return true
*  Else, no cycle exists and we return false


_Time Complexity:_ O(m+n), where m is the number of edges and n is the number of nodes

_Time taken to execute:_ 1ms

![image](https://user-images.githubusercontent.com/97650586/165834644-4bf10dfd-ecf8-48c7-bd2d-fa26390bdf18.png)


![image](https://user-images.githubusercontent.com/97650586/165834746-5e2c2b03-cdf2-4f80-91f5-31d7317321a3.png)


## **_8. DeliveringTrojan_**

`std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations,
                                                     std::vector<std::vector<std::string>> &dependencies)`

* **Input:** List of locations to be visited and the dependency order
* **Output:** Returns the topological sorted order of locations

*  Create a directed graph from the given inputs
*  If this graph contains a cycle, return an empty vector
*  Else it is a DAG
*  Mark all the location nodes as unvisited 
*  Loop through each location. If its DAG neighbour is unvisited, call the function recursively and mark the node as visited
*  Push the visited node to the result vector after all the neighbours have been visited
*  Return the reversed result vector

_Time Complexity:_ O(m+n), where m is the number of edges and n is the number of nodes

_Time taken to execute (for 3 nodes):_ 24us

![image](https://user-images.githubusercontent.com/97588998/166088067-6e45e8bc-056d-4e63-92c3-0cf2284aa1c5.png)

![image](https://user-images.githubusercontent.com/97588998/166088083-9c378c26-0be4-4082-b1c2-1b8230c2dca3.png)

## **_9. TravellingSalesman_BruteForce_**

`std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_Backtracking(
                                                                                        std::vector<std::string> location_ids)`

* **Input:** List of locations to be visited
* **Output:** Returns a pair of the minimum distance path and a list of all the paths traversed

*  Begin traversing the connected graph from the start node
*  If the path length reaches the maximum, push this path into the result
*  Calculate the path length. If it is less than minimum, replace minimum with the current path length
*  Loop through the other nodes in the input list. If, the node is absent in the current path call the function recursively after adding this node to the path

_Time Complexity:_ O(n!), where n is the number of nodes

_Time taken to execute (for 8 nodes):_ 78ms

![image](https://user-images.githubusercontent.com/97650586/165835936-91ffc082-74b8-45bf-898b-e146d5f751dc.png)


## **_10. TravellingSalesman_Backtracking_**

`std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_Brute_force(
                                                           std::vector<std::string> location_ids)`

* **Input:** List of locations to be visited
* **Output:** Returns a pair of the minimum distance path and a list of all the paths traversed

*  Begin traversing the connected graph from the start node
*  If we reach a leaf node, push this path into the result
*  Calculate the path length. If it is less than minimum, replace minimum with the current path length
*  If the current path length > minimum path length, do an early return
*  Loop through the other nodes in the input list. If, the node is absent in the current path call the function recursively after adding this node to the path

_Time Complexity:_ O(n!), where n is the number of nodes

_Time taken to execute (for 8 nodes):_ 47ms

![image](https://user-images.githubusercontent.com/97650586/165837052-a2cada81-acfe-462a-bf3a-62f68cb84d93.png)


## **_11. TravellingSalesman_2-opt Heuristic_**

`std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_2opt(
                                                                        std::vector<std::string> location_ids)`

* **Input:** List of locations to be visited
* **Output:** Returns a pair of the minimum distance path and a list of all the paths traversed

*  Use two for loops to traverse through all the nodes
*  The first for loop (i) starts from the second node(start node should not be swapped)
*  The second for loop (j) starts one node ahead of the previous for loop
*  Swap the nodes at i and j and calculate the new path length and push this path into the result
*  If this path length < minimum path length, replace minimum with the current path length
*  Continue until no improvement is made

_Time Complexity:_ O(n<sup>2</sup>), where n is the number of nodes

_Time taken to execute (for 8 nodes):_ 0.3ms

![image](https://user-images.githubusercontent.com/97650586/165836986-4e991818-8874-45ad-901d-fd8356d027ea.png)


## **_12. FindNearby_**

`std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k)`

* **Input:** Attributes, Location Name, Radius of area and number of nearest neighbor locations
* **Output:** Returns a vector of k nearest locations

*  We loop through all the elements of the map 'data' 
*  If the element's attribute matches the input attribute, check whether it lies within distance r from the input location
*  If it does, push it into the max heap
*  If the size of max heap is already k, check if the current element's distance < maximum distance. If yes, replace the maximum distance node with the current node
*  Transfer the max heap elements to the result vector

_Time Complexity:_ O(nlog(k)), where n is the number of nodes and k is number of nearest neighbor locations

![image](https://user-images.githubusercontent.com/97650586/165835523-970ef3bd-6fb4-4991-b7dd-be2f0c62b01c.png)

![image](https://user-images.githubusercontent.com/97650586/166077184-8927b8cd-381d-4ebd-a120-8f12def71a3f.png)


## Extra credit items

## **_13. TravellingSalesman_GeneticAlgorithm_**

`std::pair<double,std::vector<std::vector<std::string>>>TrojanMap::TravellingTrojan_GeneticAlgo( std::vector<std::string> location_ids)`

* **Input:** List of locations to be visited
* **Output:** Returns a pair of the minimum distance path and a list of all the paths traversed

*  Population size, cooling variable and number of iterations are initialized
*  While loop is used to keep iterating until we have a valid cooling variable or number of iterations reach a maximum
*  A new set of chromosomes/paths are created in each loop iteration from the previous parent generation
*  Gene mutation is done by randomly swapping any two genes in the chromosome
*  Fitness of the mutation is calculated. Based on this value, it isi decided whether it is a part of the next generation or not

_Time Complexity:_ O(g(nm + nm + n)), where g is the number of generations, n is the population size and m is the size of the individuals

_Time taken to execute (for 8 nodes):_ 0.3ms

![image](https://user-images.githubusercontent.com/97650586/165836887-59fe5222-d104-40c2-8abd-28d027b3ddec.png)



## **_14. CalculateShortestPath_BFS_**

`std::vector<std::string> TrojanMap::CalculateShortestPath_BFS(std::string location1_name, std::string location2_name)`

* **Input:** User enters two location names
* **Output:** Returns a vector with shortest path

*  Initialize distance to each node as DBL_MAX
*  If user enters invalid location name, then empty vector is returned
*  Update the distance of the starting node to 0
*  Create a queue and push the starting node into it
*  Get the top most element of the queue, if this is equal to the destination location, break from the loop
*  Mark this node as visited
*  Run the below steps till the queue is empty:
*  Loop through the node's neighbours. If its current distance > predecessor distance + edge distance, then update the node's distance with predecessor distance + edge distance 
*  Push this node in the queue
*  After the second location is obtained, reverse the path vector and return the path

_Time Complexity:_ O(m+n), where m is the number of edges and n is the number of nodes

_Time taken for completion:_ 47ms

![image](https://user-images.githubusercontent.com/97650586/165835066-86430f1a-43d0-4699-8e86-fe2eced71c88.png)


# Discussion

* Calculating Closest Name using Edit Distance without Dynamic Programming takes more than 10 minutes and the search is aborted
* We see that the execution time for Topological Sort keeps increasing as we add more number of nodes and dependencies

![image](https://user-images.githubusercontent.com/97588998/165997835-99fc1a78-22d3-434b-b0eb-04781eb6d08c.png)

* Calculating shortest path (for the same number of nodes) using Bellman Ford takes much longer time than using Dijkstra's algorithm. The runtime for BFS and Dijkstra are approximately the same, however, BFS does not always return the shortest path

![image](https://user-images.githubusercontent.com/97588998/165998114-7bfce6fa-bcc8-450c-beda-92d346663fe8.png)

* Brute force TSP implementation gets exhausted if there are more than 12 nodes. Early backtracking also fails to work if there are more than 16 nodes. 
* 2-opt and Genetic Algo prove to be extrememly useful here since their execution time is exponentially lower than that of Brute Force and Early Backtracking, yet they provide 'close to optimal' solutions for the Travelling Salesman problem

![image](https://user-images.githubusercontent.com/97650586/165998873-284cf723-fbbd-40ed-b8e5-c0de77c3a6be.png)

* Genetic Algorithm executes faster than 2-opt for the same number of nodes and gives approximately the samae path length.
* Testing was done in such a way so as to ensure that output remains the same even when interchanging the destination and source for shortest Path algorithms.
* Test cases were designed to handle corner cases so that outlying conditions do not affect the final result. 

# Learnings

* Understanding the importance of optimization techniques, such as memoization and backtracking, and their heuristics in real world applications when you have large amounts of data
* Relation of the genetic algorithm, which is based on the principal of evolution and survival of the fittest to travelling salesman implementation
* Efficiently being able to access and handle data using STLs
* Importance of the role of testing to not only test your code, but to be able to catch corner case bugs.


# Conclusion
We have implemented the Trojan Map application as a guide to navigate through USC and its surrounding areas. We learnt and used many diverse algorithms in the project ranging from shortest path algorithms (such as Dijkstra and Bellman-Ford) to TSP implementations (such as Backtracking and Genetic Algo) and edit distance calculations. We were able to get an insight into how Google Maps functions from within and aim to implement an extension of our project to the entire LA county. 
