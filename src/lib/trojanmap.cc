#include "trojanmap.h"

//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
bool lessthan1(struct individual t1,
            struct individual t2)
  {
    return t1.fitness < t2.fitness;
  }

  int min(int x, int y, int z){
  return std::min(std::min(x, y), z);
  }

/**
 * GetLat: Get the latitude of a Node given its id. If id does not exist, return -1.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(const std::string& id) {
    if (data.count(id) > 0)
      return data[id].lat;
    else
      return -1;
}

/**
 * GetLon: Get the longitude of a Node given its id. If id does not exist, return -1.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(const std::string& id) { 
    if(data.count(id) > 0)
      return data[id].lon;
    else
      return -1;
}

/**
 * GetName: Get the name of a Node given its id. If id does not exist, return "NULL".
 * 
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(const std::string& id) { 
  if(data.count(id) > 0)
      return data[id].name;
  else
    return "NULL";
    
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node. If id does not exist, return an empty vector.
 * 
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(const std::string& id) {
    std::vector<std::string> res;
    if(data.count(id) > 0){
      res = data[id].neighbors;
    }
    return res;
}

/**
 * GetID: Given a location name, return the id. 
 * If the node does not exist, return an empty string. 
 *
 * @param  {std::string} name          : location name
 * @return {int}  : id
 */
std::string TrojanMap::GetID(const std::string& name) {
  std::string res = "";
  for(auto &i : data){
    if (i.second.name == name){
      res = i.first;
    }
  }
  return res;
}

/**
 * GetPosition: Given a location name, return the position. If id does not exist, return (-1, -1).
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {

  std::pair<double, double> results(-1, -1);
  if(name.size() == 0){
    return results;
  }
  for(auto &i : data){
    if(i.second.name == name){
      results.first = i.second.lat;
      results.second = i.second.lon;
      break;
    }
  }
  return results;

}


/**
 * CalculateEditDistance: Calculate edit distance between two location names
 * 
 */
int TrojanMap::CalculateEditDistance(std::string a, std::string b){
    std::vector<std::vector<int>> memo (a.size()+1, std::vector<int>(b.size()+1, 0));
    std::transform(a.begin(), a.end(), a.begin(), ::tolower);
    std::transform(b.begin(), b.end(), b.begin(), ::tolower);
    for (int i = 0;i < b.size()+1; i++){
      memo[0][i] = i;
    }

    for(int j = 0;j< a.size()+1; j++){
      memo[j][0] = j;
    }

    for(int i = 1; i<a.size()+1; i++){
      for(int j = 1; j<b.size()+1; j++){

        if(a[i-1] == b[j-1]){
          int minimum = std::min(memo[i-1][j], memo[i][j-1]);
          memo[i][j] = 1 + std::min(minimum, memo[i-1][j-1]-1);
        }

        if(a[i-1] != b[j-1]){
          int minimum = std::min(memo[i-1][j], memo[i][j-1]);
          memo[i][j] = 1 + std::min(minimum, memo[i-1][j-1]);
        }
      }
    }

    return memo[a.size()][b.size()];
}

int TrojanMap::CalculateEditDistancewoDP(std::string a, std::string b, clock_t start_time){
  std::transform(a.begin(), a.end(), a.begin(), ::tolower);
  std::transform(b.begin(), b.end(), b.begin(), ::tolower);
  clock_t now;
  if(a.size() == 0){
    return b.size();
  }
  if(b.size() == 0){
    return a.size();
  }
  now = clock();
    if(((now - start_time) / CLOCKS_PER_SEC) >= 600){
        std::cout<<"Search timed out"<<std::endl;
        exit(1);
    }
  std::string a1 = a.substr(0, a.size()-1);
  std::string b1 = b.substr(0, b.size()-1);
  if(a[a.size()-1] == b[b.size()-1]){
    return CalculateEditDistancewoDP(a1, b1, start_time);
  }
  return 1+min(CalculateEditDistancewoDP(a, b1, start_time), CalculateEditDistancewoDP(a1, b, start_time), CalculateEditDistancewoDP(a1, b1, start_time));
}

/**
 * FindClosestName: Given a location name, return the name with smallest edit distance.
 *
 * @param  {std::string} name          : location name
 * @return {std::string} tmp           : similar name
 */
std::string TrojanMap::FindClosestName(std::string name) {
  std::string tmp = "";
  int min=INT_MAX;
  
  for(auto &i:data)
  {
    int actual=CalculateEditDistance(i.second.name,name);
    if(actual<min)
    {
      min=actual;
      tmp=i.second.name;
    }
  }
  return tmp;
}


/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix. The function should be case-insensitive.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name){
  std::vector<std::string> results;
 

  std::transform(name.begin(), name.end(), name.begin(), ::tolower);

  if (name.size()==0)
    return results;

  for (auto &i : data) 
  {
    std::string subset=i.second.name;    
    std::transform(subset.begin(), subset.end(), subset.begin(), ::tolower);
  
    if (name.size()>subset.size()) 
    {
      continue;
    }

    if (name == subset.substr(0, name.size())) 
    {
      results.push_back(i.second.name);
    }
    
  }   

  return results;
}

/**
 * CalculateDistance: Get the distance between 2 nodes. 
 * 
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id, const std::string &b_id) {
  // Do not change this function
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2),2.0) + cos(a.lat * M_PI / 180.0) * cos(b.lat * M_PI / 180.0) * pow(sin(dlon / 2),2.0);
  double c = 2 * asin(std::min(1.0,sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations inside the vector.
 * 
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  for (int i = 0;i < int(path.size())-1; i++) {
    sum += CalculateDistance(path[i], path[i+1]);
  }
  return sum;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path which is a
 * list of id. Hint: Use priority queue.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {
    std::vector<std::string> path;
    bool flag = false;
    std::unordered_map<std::string, std::pair<std::string, double>> dist(data.size());
    std::unordered_map<std::string, bool> visited;

    for(auto &i:data){
      dist[i.first] = std::make_pair("", DBL_MAX);
    }
    std::string id1 = GetID(location1_name);
    std::string id2 = GetID(location2_name);
    if((location1_name == "") || (location2_name == "") || (id1 == "") || (id2 == "")){
      return path;
    }
    //dist[id1] = std::make_pair(id1, 0);
    dist[id1].second = 0;
    std::priority_queue<std::pair<double, std::string>, 
                                  std::vector<std::pair<double, std::string>>, 
                                  std::greater<std::pair<double, std::string>>> prior_q;
    prior_q.push(std::make_pair(0, id1));
    while(!prior_q.empty()){
      std::string min_loc_id = prior_q.top().second;
      if(min_loc_id == id2){
        flag = true;
        break;
      }
      visited[min_loc_id] = true;
      prior_q.pop();
      for(auto &j:data[min_loc_id].neighbors){
        if(visited[j] == true){
          continue;
        }
        double min_distance = dist[min_loc_id].second + CalculateDistance(min_loc_id, j);
        if(dist[j].second > min_distance){
          dist[j].second = min_distance;
          dist[j].first = min_loc_id;
          prior_q.push(std::make_pair(min_distance, j));
        }
      }
    }

    if(flag == false){
      return path;
    }

    std::string k = id2;
    while(k != ""){
      path.push_back(k);
      k = dist[k].first;
    }
  std::reverse(path.begin(), path.end());
  return path;
}

/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest path which is a
 * list of id. Hint: Do the early termination when there is no change on distance.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
    std::string location1_name, std::string location2_name){
  std::vector<std::string> path;
  bool flag = false;
  std::string id1 = GetID(location1_name);
  std::string id2 = GetID(location2_name);
  if((location1_name == "") || (location2_name == "") || (id1 == "") || (id2 == "")){
    return path;
  }
  std::unordered_map<std::string, std::pair<std::string, double>> dist(data.size());

  for(auto &i:data){
    dist[i.first] = std::make_pair("", DBL_MAX);
  }
  dist[id1].second = 0;
  for(int i = 0; i<data.size()-1; i++){
    flag = false;
    for(auto &j : data){
      for(auto &k : j.second.neighbors){
        double min_distance = dist[j.first].second + CalculateDistance(k, j.first);
        if(dist[k].second > min_distance){
          dist[k].second = min_distance;
          dist[k].first = j.first;
          flag = true;
        }
      }
    }
    if(flag == false){
        break;
    }
  }

  std::string k = id2;
  while(k != ""){
    path.push_back(k);
    k = dist[k].first;
  }
  std::reverse(path.begin(), path.end());
  return path;
}

std::vector<std::string> TrojanMap::CalculateShortestPath_BFS(std::string location1_name, std::string location2_name){
  std::vector<std::string> path;

  std::string id1 = GetID(location1_name);
  std::string id2 = GetID(location2_name);
  bool flag = false;
  std::unordered_map<std::string, std::pair<std::string, double>> dist(data.size());
  std::unordered_map<std::string, bool> visited;
  std::queue<std::string> q;
  for(auto &i:data){
      dist[i.first] = std::make_pair("", DBL_MAX);
  }

  if((location1_name == "") || (location2_name == "") || (id1 == "") || (id2 == "")){
    return path;
  }
  dist[id1].second = 0;
  visited[id1] = true;
  q.push(id1);

  while(!q.empty()){
    std::string u = q.front();
    q.pop();
    for(auto &i : data[u].neighbors){
      if(visited[i] == false){
        visited[i] = true;
        dist[i].second = dist[u].second + CalculateDistance(u, i);
        dist[i].first = u;
        q.push(i);

        if(i == id2){
          flag = true;
        }
      }
    }
    if(flag == true){
      break;
    }
  }
  std::string k = id2;
  while(k != ""){
    path.push_back(k);
    k = dist[k].first;
  }
  std::reverse(path.begin(), path.end());
  return path;
}


void TrojanMap::TSP_Aux(clock_t start_time, int start, int size, int cur_node, double &min_cost,
                          std::vector<std::string> &cur_path, std::unordered_map<int, std::string> &location_map,
                          std::pair<double, std::vector<std::vector<std::string>>> &records){
    
    clock_t now; 
    if(cur_path.size() == size){
      cur_path.push_back(location_map[start]);
      double final_cost = CalculatePathLength(cur_path);
      records.second.push_back(cur_path);
      cur_path.pop_back();

      if(final_cost < min_cost){
        min_cost = final_cost;
      }
      return;
    }

    now = clock();
    if(((now - start_time) / CLOCKS_PER_SEC) >= 600){
      std::cout << "Search timed out." << std::endl;
        exit(1);
    }
    for(int i = 0;i<size; i++){
      if(std::find(cur_path.begin(), cur_path.end(), location_map[i]) != cur_path.end()){
        continue;
      }
      cur_path.push_back(location_map[i]);
      TSP_Aux(start_time, start, size, i, min_cost, cur_path, location_map, records);
      cur_path.pop_back();
    }
}
 
/**
 * Travelling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Brute_force(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  std::unordered_map<int, std::string> location_map;
  double min_cost = DBL_MAX;
  int start = 0;
  int size = location_ids.size();

  for(int i = 0; i<location_ids.size(); i++){
    location_map[i] = location_ids[i];
  }
  std::vector<std::string> cur_path = {location_map[start]};

  records.first = DBL_MAX;
  double distance;
  clock_t start_time = clock();
  TSP_Aux(start_time, start, size, start, min_cost, cur_path, location_map, records);
  records.first = min_cost;

  for(int i = 0;i<records.second.size();i++){
    distance = CalculatePathLength(records.second[i]);
    if(distance == records.first){
      records.second.push_back(records.second[i]);
      records.second.erase(records.second.begin() + i);
    }
  }

  return records;
}


void TrojanMap::TSP_Aux_BackTrack(clock_t start_time, int start, int size, int cur_node, double &min_cost,
                          std::vector<std::string> &cur_path, std::unordered_map<int, std::string> &location_map,
                          std::pair<double, std::vector<std::vector<std::string>>> &records){
    
    clock_t now;
    if(cur_path.size() == size){
      cur_path.push_back(location_map[start]);
      double final_cost = CalculatePathLength(cur_path);
      records.second.push_back(cur_path);
      cur_path.pop_back();

      if(final_cost < min_cost){
        min_cost = final_cost;
      }
      return;
    }

    double cur_cost = CalculatePathLength(cur_path);
    if(cur_cost > min_cost){
      return;
    }
    now = clock();
    if(((now - start_time) / CLOCKS_PER_SEC) >= 600){
      std::cout << "Search timed out." << std::endl;
        exit(1);
    }

    for(int i = 0;i<size; i++){
      if(std::find(cur_path.begin(), cur_path.end(), location_map[i]) != cur_path.end()){
        continue;
      }
      cur_path.push_back(location_map[i]);
      TSP_Aux_BackTrack(start_time, start, size, i, min_cost, cur_path, location_map, records);
      cur_path.pop_back();
    }
 }


std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Backtracking(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  std::unordered_map<int, std::string> location_map;
  double min_cost = DBL_MAX;
  int start = 0;
  int size = location_ids.size();
  
  for(int i = 0; i<location_ids.size(); i++){
    location_map[i] = location_ids[i];
  }
  std::vector<std::string> cur_path = {location_map[start]};

  records.first = DBL_MAX;
  double distance;
  clock_t start_time = clock();
  TSP_Aux_BackTrack(start_time, start, size, start, min_cost, cur_path, location_map, records);
  records.first = min_cost;

  for(int i = 0;i<records.second.size();i++){
    distance = CalculatePathLength(records.second[i]);
    if(distance == records.first){
      records.second.push_back(records.second[i]);
      records.second.erase(records.second.begin() + i);
    }
  }

  return records;
}


void TrojanMap::Two_Opt(int node_1, int node_2, bool &flag, std::vector<std::string> &location_ids, double &min_dist, 
                      std::pair<double, std::vector<std::vector<std::string>>> &records){
  std::vector<std::string> cur_path;
  for(int k = 0; k < node_1; k++){
    cur_path.push_back(location_ids[k]);
  }
  //cur_path.push_back(location_ids[node_2]);
  //for(int k = node_1; k < node_2; k++){
    //cur_path.push_back(location_ids[k]);
  //}
  for(int k = node_2; k >= node_1; k--){
    cur_path.push_back(location_ids[k]);
  }
  for(int k = node_2+1; k<location_ids.size(); k++){
    cur_path.push_back(location_ids[k]);
  }
  cur_path.push_back(location_ids[0]);
  double new_dist = CalculatePathLength(cur_path);
  if(new_dist < min_dist){
    flag = true;
    min_dist = new_dist;
    records.second.push_back(cur_path);
  }
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_2opt(
      std::vector<std::string> location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> records;

  double best_distance = DBL_MAX;
  //records.second.push_back(location_ids);
  bool flag = true;

  while(flag){
    flag = false;
    for(int i = 1;i<location_ids.size()-1; i++){
      for(int j = i+1; j<location_ids.size(); j++){
        Two_Opt(i, j, flag, location_ids, best_distance, records);
      }
    }
    if(flag == false){
      break;
    }
  }
  records.first = best_distance;
  double distance;

  for(int i = 0;i<records.second.size();i++){
    distance = CalculatePathLength(records.second[i]);
    if(distance == records.first){
      records.second.push_back(records.second[i]);
      records.second.erase(records.second.begin() + i);
    }
  }
  //std::vector<std::string> a = records.second[records.second.size()-1];
  //std::cout<<"####Final Path";
  //for(int i = 0;i<a.size(); i++)
  //{
    //std::cout<<a[i]<<" ";
  //}
  //std::cout<<"####Size 3"<<records.second.size();
  return records;
}

void TrojanMap::TSP_Util(std::vector<std::vector<double>> weights, std::pair<double, std::vector<std::vector<std::string>>> &records, 
                        double &dist){
  // Generation Number 
    int gen = 1; 
    // Number of Gene Iterations 
    int gen_thres = 10; 
    // Population Size
    int POP_SIZE = 10;
    
    
    std::vector<struct individual> population; 
    struct individual temp;

    // Populating the GNOME pool. 
    for (int i = 0; i < POP_SIZE; i++) { 
        temp.gnome = create_gnome(weights); 
        temp.fitness = cal_fitness(temp.gnome, weights); 
        population.push_back(temp); 
    } 

    for (int i = 0; i < POP_SIZE; i++){
        dist+=population[i].fitness;
    }
    dist = dist/population.size();

    int temperature = 10000; 

    // Iteration to perform 
    // population crossing and gene mutation. 
    while (temperature > 1000 && gen <= gen_thres) { 
        std::sort(population.begin() , population.end(), lessthan1);
        std::vector<struct individual> new_population; 
  
        for (int i = 0; i < POP_SIZE; i++) { 
            struct individual p1 = population[i]; 
          
            while (true) { 
               
                std::string new_g = mutatedGene(p1.gnome, weights); 
                struct individual new_gnome; 
                new_gnome.gnome = new_g; 
                new_gnome.fitness = cal_fitness(new_gnome.gnome, weights); 
                
                if (new_gnome.fitness <= population[i].fitness) { 
                    new_population.push_back(new_gnome); 
                    break; 
                } 
                else { 
                      // Accepting the rejected children at 
                      // a possible probablity above threshold. 
                      float prob = pow(2.7, 
                                     -1 * ((float)(new_gnome.fitness 
                                                   - population[i].fitness) 
                                           / temperature)); 
                    if (prob > 0.9) { 
                        new_population.push_back(new_gnome); 
                        break; 
                    } 
                }
            } 
        }

        temperature = cooldown(temperature); 
        population = new_population; 
        double min = population[0].fitness;
        int min_gnome;
        for (int i = 0; i < POP_SIZE; i++)
        { 
          if(population[i].fitness < min)
          {
            min = population[i].fitness;
            min_gnome = i;
          }
        }
        std::vector<std::string> x;
        x.push_back(population[min_gnome].gnome);
        records.first = min;
        records.second.push_back(x);
        gen++; 
    }  
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_GeneticAlgo(
     std::vector<std::string> location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> records;
  std::pair<double, std::vector<std::vector<std::string>>> result;
  records.first = DBL_MAX;
  std::map<int, std::string>location_map;

  double distance;
  std::vector<std::vector<double>> weights(location_ids.size(), std::vector<double> (location_ids.size()));

  for(int i = 0; i < location_ids.size(); i++){
    location_map[i] = location_ids[i];
  }

  for(int i = 0; i < location_ids.size(); i++){ 
    for(int j = 0; j < location_ids.size(); j++){
      if(i == j){
        weights[i][j] = 0;
      }
      else{      
      distance = CalculateDistance(location_ids[i], location_ids[j]);      
      weights[i][j] = distance;
      }
    }
  }
  double dist = 0;
  TSP_Util(weights, records, dist);

  result.first = records.first;
  std::cout<<"Initial population average"<<" "<<dist<<" miles\n";
  std::cout<<"Distance after multiple mutations"<<" "<<result.first<<" miles\n";
  std::cout<<"Improvement of"<<" "<<dist-result.first<<" miles\n\n";

  
  for(int i = 0; i < records.second.size(); i++)
  {
    std::vector<std::string> x;
    for(int j = 0; j < records.second[i].size(); j++)
    {
      for(int k = 0; k < records.second[i][j].size(); k++)
      {
        int z = (int)records.second[i][j][k] - 48;
        x.push_back(location_map[z]);
      }
    }
    result.second.push_back(x);
  }

  //std::cout<<"####Size4"<<result.second.size();
  //std::cout<<"####Final path";
  //std::vector<std::string> a = result.second[result.second.size()-1];
  //for(int i = 0;i<a.size(); i++)
  //std::cout<<a[i]<<" ";
  //std::cout<<"####Distance4"<<CalculatePathLength(a);

  return result;
}

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations 
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(std::string locations_filename){
  std::vector<std::string> location_names_from_csv;
  std::string line;
  std::fstream fin;
  fin.open(locations_filename, std::ios::in);
  getline(fin, line);
  while(getline(fin, line)){
      location_names_from_csv.push_back(line);
  }
  fin.close();
  return location_names_from_csv;
}


/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(std::string dependencies_filename){
  std::vector<std::vector<std::string>> dependencies_from_csv;
  std::string line;
  std::vector<std::string> dependency;
  std::fstream fin;

  fin.open(dependencies_filename, std::ios::in);
  getline(fin, line);

  while(getline(fin, line)) {
    std::stringstream ss(line);
    std::string dependency1;
    std::string dependency2;
    std::getline(ss, dependency1, ',');
    std::getline(ss, dependency2);
    dependency = {dependency1, dependency2};
  
    dependencies_from_csv.push_back(dependency);
  }

  fin.close();

  return dependencies_from_csv;
}


/**
 * DeliveringTrojanHelper: Given a location name and the dependency matrix, it returns a sorting of nodes
 * that satisfies the given dependencies.
 *
 * @param  {std::string} location                                                           : location_id
 * @param  {std::unordered_map<std::string, bool>} visited                                  : list of visited nodes
 * @param  {std::unordered_map<std::string, std::vector<std::string>>} dependency_order     : dependency order matrix
 * @return {std::vector<std::string>} result                                                : results
 */
void TrojanMap::DeliveringTrojanHelper(std::string location, 
                                                     std::unordered_map<std::string, bool> &visited,
                                                     std::unordered_map<std::string, std::vector<std::string>> &dependency_order,
                                                     std::vector<std::string> &result){
  visited[location] = true;
  std::vector<std::string> order = dependency_order[location];
  if(order.size()>0){
    for(auto &i : order){
      if(visited[i] == false){
        DeliveringTrojanHelper(i, visited, dependency_order, result);
      }
    }
  }
  result.push_back(location);
}
bool TrojanMap::IsDAGHelper(std::string location, std::unordered_map<std::string, int> &visited,
                 std::unordered_map<std::string, std::vector<std::string>> &dependency_order){
  visited[location] = 1; //being visited
  std::vector<std::string> order = dependency_order[location];
  if(order.size()>0){
    for(auto &i : order){
      if(visited[i] == 0){
        if(IsDAGHelper(i, visited, dependency_order) == true){
          return true;
        }
      }
      else if(visited[i] == 1){
        return true;
      }  
    }
  }
  visited[location] = 2; //visited
  return false;
}
bool TrojanMap::IsDAG(std::unordered_map<std::string, std::vector<std::string>> dependency_order){
  std::unordered_map<std::string, int> visited;
  for(auto &i : dependency_order){
    visited[i.first] = 0; //unvisited
  }
  for(auto &i : dependency_order){
    if(visited[i.first] == 0){
      if(IsDAGHelper(i.first, visited, dependency_order) == true){
        return true;
      }
    }
  }
  return false;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a sorting of nodes
 * that satisfies the given dependencies. If there is no way to do it, return a empty vector.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations,
                                                     std::vector<std::vector<std::string>> &dependencies){
  
  std::vector<std::string> result;
  std::unordered_map<std::string, bool> visited;
  std::unordered_map<std::string, std::vector<std::string>> dependency_order;

  for(auto &i : locations){
    visited[i] = false;
  }
  for(auto &i : dependencies){
    for(int j = 0;j<i.size()-1; j++){
      dependency_order[i[0]].push_back(i[j+1]);
    }
  }
  bool res =  IsDAG(dependency_order);
  if(res){
    return result;
  }
  for(auto&i : locations){
    if(visited[i] == false){
      DeliveringTrojanHelper(i, visited, dependency_order, result);
    }
  }

  std::reverse(result.begin(), result.end());
  return result;                                                     
}


/**
 * inSquare: Give a id retunr whether it is in square or not.
 *
 * @param  {std::string} id            : location id
 * @param  {std::vector<double>} square: four vertexes of the square area
 * @return {bool}                      : in square or not
 */
bool TrojanMap::inSquare(std::string id, std::vector<double> &square) {
  Node n = data[id];
  double lon_id = n.lon;
  double lat_id = n.lat;
  if((lon_id > square[0]) && (lon_id < square[1]) && (lat_id < square[2]) && (lat_id > square[3])){
    return true;
  }
  return false;
}

/**
 * GetSubgraph: Give four vertexes of the square area, return a list of location ids in the squares
 *
 * @param  {std::vector<double>} square         : four vertexes of the square area
 * @return {std::vector<std::string>} subgraph  : list of location ids in the square
 */
std::vector<std::string> TrojanMap::GetSubgraph(std::vector<double> &square) {
  // include all the nodes in subgraph
  std::vector<std::string> subgraph;
  for(auto &i : data){

    if(inSquare(i.first, square)){
      subgraph.push_back(i.first);
    }
  }
  return subgraph;
}

/**
 * Cycle DetectionHelper: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square and form the path, false otherwise.
 * 
 * @param {std::string} id: source location id
 * @param {std::vector<double>} square: four vertexes of the square area
 * @param {std::unordered_map<std::string, std::vector<std::string>>} cycle_path: fill the cycle path
 * @param {std::unordered_map<std::string, bool>} visited: List of visited nodes
 * @param {std::string parent} parent: Predecessor of location id
 * @return {bool}: whether there is a cycle or not
 */
bool TrojanMap::CycleDetectionHelper(std::string id, std::vector<double> &square, 
                                     std::unordered_map<std::string, std::vector<std::string>> &cycle_path, 
                                     std::unordered_map<std::string, bool> &visited, std::string parent){

  visited[id] = true;
  for(auto &j : data[id].neighbors){
    if(!inSquare(j, square)){
      continue;
    }
    if(!visited[j]){
      if(CycleDetectionHelper(j, square, cycle_path, visited, id)){
        cycle_path[j].push_back(id);
        return true;
      }
    }
    else if(j != parent){
      return true;
    }
  }
  return false;
}
/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square, false otherwise.
 * 
 * @param {std::vector<std::string>} subgraph: list of location ids in the square
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */
bool TrojanMap::CycleDetection(std::vector<std::string> &subgraph, std::vector<double> &square) {
  
  std::unordered_map<std::string, bool> visited;
  std::unordered_map<std::string, std::vector<std::string>> cycle_path;
  bool result = false;

  for(auto &i : subgraph){
    visited[i] = false;
  }
  for(auto &i : subgraph){
    if(!visited[i]){
      result = CycleDetectionHelper(i, square, cycle_path, visited, i);
      if(result == true){
        //MapUI m;
        //m.PlotPath(cycle_path[i]);
        break;
      }
    }
  }
  return result;
}

/**
 * FindNearby: Given a class name C, a location name L and a number r, 
 * find all locations in class C on the map near L with the range of r and return a vector of string ids
 * 
 * @param {std::string} className: the name of the class
 * @param {std::string} locationName: the name of the location
 * @param {int} r: search radius
 * @param {int} k: search numbers
 * @return {std::vector<std::string>}: location name that meets the requirements
 */
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k) {
  std::vector<std::string> res;
  double distance;
  bool flag = false;
  std::unordered_set<std::string> temp;
  std::priority_queue<std::pair<double, std::string>> locations;
  std::string start_id = GetID(name);

  if((k <= 0) || (r <= 0)){
    return res;
  }
  if(start_id == ""){
    return res;
  }

  for(auto &i : data){
    flag = false;
    if(i.first == start_id){
      continue;
    }

    temp = i.second.attributes;
    for(auto j = temp.begin(); j != temp.end(); j++){
      if(*j == attributesName){
        flag = true;
      }
    }
    if(flag == true){
      distance = CalculateDistance(i.first, start_id);
      if(distance <= r){
        if(locations.size() >= k){
          if(distance < locations.top().first){
            locations.push(std::make_pair(distance, i.first));
            locations.pop();
          }
        }
        else{
          locations.push(std::make_pair(distance, i.first));
        }
      }
    }
  }
  while(!locations.empty()){
    res.push_back(locations.top().second);
    locations.pop();
  }
  std::reverse(res.begin(), res.end());
  return res;
}

/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * 
 */
void TrojanMap::CreateGraphFromCSVFile() {
  // Do not change this function
  std::fstream fin;
  fin.open("src/lib/data.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '{'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '}'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        if (isalpha(word[0]))
          n.attributes.insert(word);
        if (isdigit(word[0]))
          n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}
