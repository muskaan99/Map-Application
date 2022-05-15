#ifndef TROJAN_MAP_H
#define TROJAN_MAP_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cfloat>
#include <ctime>
#include <math.h>
#include <fstream>
#include <sstream>
#include <climits>

// A Node is the location of one point in the map.
class Node {
  public:
    Node(){};
    Node(const Node &n){id = n.id; lat = n.lat; lon = n.lon; name = n.name; neighbors = n.neighbors; attributes = n.attributes;};
    std::string id;    // A unique id assign to each point
    double lat;        // Latitude
    double lon;        // Longitude
    std::string name;  // Name of the location. E.g. "Bank of America".
    std::vector<std::string> neighbors;  // List of the ids of all neighbor points.
    std::unordered_set<std::string> attributes;  // List of the attributes of the location.
};

struct individual
{
  std::string gnome;
  double fitness;
  //bool operator < ( const individual&  item )const
  //{
    //  return fitness < item.fitness;
  //}
};

class TrojanMap {
 public:
  // Constructor
  TrojanMap(){CreateGraphFromCSVFile();};
  
  // A map of ids to Nodes.
  std::unordered_map<std::string, Node> data;  

  //-----------------------------------------------------
  // Read in the data
  void CreateGraphFromCSVFile();

  //-----------------------------------------------------
  // TODO: Implement these functions and create unit tests for them:
  // Get the Latitude of a Node given its id.
  double GetLat(const std::string& id);

  // Get the Longitude of a Node given its id.
  double GetLon(const std::string& id);

  // Get the name of a Node given its id.
  std::string GetName(const std::string& id);

  // Get the id given its name.
  std::string GetID(const std::string& name);

  // Get the neighbor ids of a Node.
  std::vector<std::string> GetNeighborIDs(const std::string& id);

  // Returns a vector of names given a partial name.
  std::vector<std::string> Autocomplete(std::string name);

  // Returns lat and lon of the given the name.
  std::pair<double, double> GetPosition(std::string name);

  // Calculate location names' edit distance
  int CalculateEditDistance(std::string, std::string);

  // Find the closest name
  std::string FindClosestName(std::string name);  

  // Get the distance between 2 nodes.
  double CalculateDistance(const std::string &a, const std::string &b);

  // Calculates the total path length for the locations inside the vector.
  double CalculatePathLength(const std::vector<std::string> &path);

  // Given the name of two locations, it should return the **ids** of the nodes
  // on the shortest path.
  std::vector<std::string> CalculateShortestPath_Dijkstra(std::string location1_name,
                                                 std::string location2_name);
  std::vector<std::string> CalculateShortestPath_Bellman_Ford(std::string location1_name,
                                                 std::string location2_name);

  // Given CSV filename, it read and parse locations data from CSV file,
  // and return locations vector for topological sort problem.
  std::vector<std::string> ReadLocationsFromCSVFile(std::string locations_filename);
  
  // Given CSV filenames, it read and parse dependencise data from CSV file,
  // and return dependencies vector for topological sort problem.
  std::vector<std::vector<std::string>> ReadDependenciesFromCSVFile(std::string dependencies_filename);

  // Given a vector of location names, it should return a sorting of nodes
  // that satisfies the given dependencies.
  std::vector<std::string> DeliveringTrojan(std::vector<std::string> &location_names,
                                            std::vector<std::vector<std::string>> &dependencies);

  // Given a vector of location ids, it should reorder them such that the path
  // that covers all these points has the minimum length.
  // The return value is a pair where the first member is the total_path,
  // and the second member is the reordered vector of points.
  // (Notice that we don't find the optimal answer. You can return an estimated
  // path.)

  std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_Brute_force(
      std::vector<std::string> location_ids);

  std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_Backtracking(
      std::vector<std::string> location_ids);
  
  std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_2opt(
      std::vector<std::string> location_ids);

  // Check whether the id is in square or not
  bool inSquare(std::string id, std::vector<double> &square);

  // Get the subgraph based on the input
  std::vector<std::string> GetSubgraph(std::vector<double> &square);

  // Given a subgraph specified by a square-shape area, determine whether there is a
  // cycle or not in this subgraph.
  bool CycleDetection(std::vector<std::string> &subgraph, std::vector<double> &square);

  // Given a location id and k, find the k closest points on the map
  std::vector<std::string> FindNearby(std::string, std::string, double, int);
  
  //----------------------------------------------------- User-defined functions
  void TSP_Util(std::vector<std::vector<double>> weights, std::pair<double, std::vector<std::vector<std::string>>> &records, 
                           double &dist);
  
  std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_GeneticAlgo(
     std::vector<std::string> location_ids);

  void DeliveringTrojanHelper(std::string location, std::unordered_map<std::string, bool> &visited,
                                                    std::unordered_map<std::string, std::vector<std::string>> &dependency_order,
                                                    std::vector<std::string> &result);
                                                    
  bool IsDAGHelper(std::string location, std::unordered_map<std::string, int> &visited,
                   std::unordered_map<std::string, std::vector<std::string>> &dependency_order);

  bool IsDAG(std::unordered_map<std::string, std::vector<std::string>> dependency_order);

  void TSP_Aux(clock_t start_time, int start, int size, int cur_node, double &min_cost,
                std::vector<std::string> &cur_path, std::unordered_map<int, std::string> &location_map,
                std::pair<double, std::vector<std::vector<std::string>>> &records);

  void TSP_Aux_BackTrack(clock_t start_time, int start, int size, int cur_node, double &min_cost,
                          std::vector<std::string> &cur_path, std::unordered_map<int, std::string> &location_map,
                          std::pair<double, std::vector<std::vector<std::string>>> &records);

  void Two_Opt(int node_1, int node_2, bool &flag, std::vector<std::string> &location_ids, double &min_dist, 
                      std::pair<double, std::vector<std::vector<std::string>>> &records);

  bool CycleDetectionHelper(std::string id, std::vector<double> &square, 
                            std::unordered_map<std::string, std::vector<std::string>> &cycle_path, 
                            std::unordered_map<std::string, bool> &visited, std::string parent);

  std::vector<std::string> CalculateShortestPath_BFS(std::string location1_name, std::string location2_name);

  int CalculateEditDistancewoDP(std::string a, std::string b, clock_t start_time);
  
 private:
  // Function to return a random number 
  // from start and end 
  int rand_num(int start, int end) 
  { 
    int r = end - start; 
    int rnum = start + rand() % r; 
    return rnum; 
  } 

  // Function to check if the character 
  // has already occurred in the string 
  bool repeat(std::string s, char ch) 
  { 
    for (int i = 0; i < s.size(); i++) { 
        if (s[i] == ch) 
            return true; 
    } 
    return false; 
  } 

  // Function to return a mutated GNOME 
  // Mutated GNOME is a string 
  // with a random interchange 
  // of two genes to create variation in species 
  std::string mutatedGene(std::string gnome, std::vector<std::vector<double>> weights) 
  {   
    int V = weights.size();
    while (true) { 
        int r = rand_num(1, V); 
        int r1 = rand_num(1, V); 
        if (r1 != r) { 
            char temp = gnome[r]; 
            gnome[r] = gnome[r1]; 
            gnome[r1] = temp; 
            break; 
        } 
    } 
    return gnome; 
}   
  std::string create_gnome(std::vector<std::vector<double>> weights) 
  { 
    int V = weights.size();
    std::string gnome = "0"; 
    while (true) { 
        if (gnome.size() == V) { 
            gnome += gnome[0]; 
            break; 
        } 
        int temp = rand_num(1, V); 
        if (!repeat(gnome, (char)(temp + 48))) 
            gnome += (char)(temp + 48); 
    } 
    return gnome; 
  } 

  // Function to return the fitness value of a gnome. 
  // The fitness value is the path length 
  // of the path represented by the GNOME. 
  double cal_fitness(std::string gnome, std::vector<std::vector<double>> weights) 
  {   
    double f = 0; 
    for (int i = 0; i < gnome.size() - 1; i++) { 
        if (weights[gnome[i] - 48][gnome[i + 1] - 48] == INT16_MAX) 
            return INT16_MAX; 
        f += weights[gnome[i] - 48][gnome[i + 1] - 48]; 
    } 

    return f; 
  } 

  // Function to return the updated value 
  // of the cooling element. 
  int cooldown(int temp) 
  { 
    return (90 * temp) / 100; 
  }

};
#endif
