#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

TEST(TrojanMapStudentTest_1, Autocomplete) {
  TrojanMap m;
  auto names = m.Autocomplete("tRiN");
  std::unordered_set<std::string> gt = {"Trinity Baptist Church L.A.", "Trinity Elementary School"}; 
  int success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());

}

///////////////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_2, Autocomplete) {
  TrojanMap m;
  auto names = m.Autocomplete("   ");
  std::vector<std::string> expected;
  EXPECT_EQ(names,expected);
}

///////////////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_3, Autocomplete) {
  TrojanMap m;
  auto names = m.Autocomplete("0");
  std::vector<std::string> expected;
  EXPECT_EQ(names,expected);
}

///////////////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_4, Autocomplete) {
  TrojanMap m;
  auto names = m.Autocomplete("8");
  std::unordered_set<std::string> gt = {"8th & Wall"}; 
  int success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
}

///////////////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_5, Autocomplete) {
  TrojanMap m;
  auto names = m.Autocomplete(";");
  std::vector<std::string> expected;
  EXPECT_EQ(names,expected);
}

///////////////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_6, FindPosition) {
  TrojanMap m;
  
  // Test Ground Zero
  auto position = m.GetPosition("Ground Zero");
  std::pair<double, double> gt1(34.0195019,-118.2822470); 
  EXPECT_EQ(position, gt1);
}
///////////////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_7, FindPosition) {
  TrojanMap m;

  // Test USC Fisher Museum of Art
  auto position = m.GetPosition("USC Fisher Museum of Art");
  std::pair<double, double> gt2(34.0186092,-118.2873476); 
  EXPECT_EQ(position, gt2);
}
///////////////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_8, FindPosition) {
  TrojanMap m;
  auto position = m.GetPosition("Muskaan");
  std::pair<double, double> gt3(-1, -1);
  EXPECT_EQ(position, gt3);
}
///////////////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_9, CalculateEditDistance) {
  TrojanMap m;
  EXPECT_EQ(m.CalculateEditDistance("abc", "Adc"), 1);
  EXPECT_EQ(m.CalculateEditDistance("Nisha", "Usha"), 2);
  EXPECT_EQ(m.CalculateEditDistance("", "Muskaan"), 7);
  EXPECT_EQ(m.CalculateEditDistance(" ", "Nisha"), 5);
}
///////////////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_10, FindClosestName) {
  TrojanMap m;
  EXPECT_EQ(m.FindClosestName("Sturbacks"), "Starbucks");
  EXPECT_EQ(m.FindClosestName("Sun Podre Street"), "San Pedro Street");
  EXPECT_EQ(m.FindClosestName("Nectar Jus bur"), "Nekter Juice Bar");
  EXPECT_EQ(m.FindClosestName(";"), "");
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
// Phase 2
// Test CalculateShortestPath_Dijkstra function
TEST(TrojanMapStudentTest_11, CalculateShortestPath_Dijkstra) {
  TrojanMap m;
  
  // Test from San Pedro Street to Nekter Juice Bar
  auto path = m.CalculateShortestPath_Dijkstra("San Pedro Street", "Nekter Juice Bar");
  std::vector<std::string> gt{
      "1866577830","2199140372","2199140366","2199140367","2199140373","2199140394",
      "2199140362","2199140392","2199140361","2199140389","2199140388","2199140379",
      "1873055966","1873055921","1873055992","67619040","1732340082","4012693767",
      "1873056002","6790384659","1732340072","1873055991","9053766706","123146084",
      "6790384665","7811710170","2613066273","122957035","1837212924","1837212927",
      "123711891","1837212923","1837212925","123711873","2613066277","123696223","123153901",
      "123153941","6818460800","6818460799","6818460805","123015367","123015369","123015371",
      "6817275189","7861033574","6805824919","123120155","4012726934","4012726933","67666150",
      "7861033558","4060105092","4060105091","4012726932","4012726929","7861033541","4060105090",
      "4060105089","123120160","122814232","122814235","122814237","122719192","123254964",
      "1732340074","21302781","7424313398","7424313397","7424313396","7424313395","7424313394",
      "7424313393","4012759744","4012759745","123280934","4012759746","4012759747","123292045",
      "123292100","9591449436","9591449432","9591449433","9591449434","9591449435","214470792",
      "5472460620","4399914049","4015405553","269633270","6820972462","4399914028","4015405552",
      "6813411585","348121996","4059993475","4399693649","4399693648","4015405549","1781230450",
      "6820935898","7023424980","1732243673","6813379489","4399693651","6814958456","1862347576",
      "4540690065","4540705198","4540705199","4540690064","4540761794"
 }; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  // Reverse the input from Nekter Juice Bar to San Pedro Street
  path = m.CalculateShortestPath_Dijkstra("Nekter Juice Bar","San Pedro Street");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

//////////////////////////////////////////////////////////////////
// Test CalculateShortestPath_Bellman_Ford function
TEST(TrojanMapStudentTest_12, CalculateShortestPath_Bellman_Ford) {
  TrojanMap m;
  // Test from San Pedro Street to Nekter Juice Bar
  auto path = m.CalculateShortestPath_Bellman_Ford("San Pedro Street", "Nekter Juice Bar");
  std::vector<std::string> gt{
      "1866577830","2199140372","2199140366","2199140367","2199140373","2199140394",
      "2199140362","2199140392","2199140361","2199140389","2199140388","2199140379",
      "1873055966","1873055921","1873055992","67619040","1732340082","4012693767",
      "1873056002","6790384659","1732340072","1873055991","9053766706","123146084",
      "6790384665","7811710170","2613066273","122957035","1837212924","1837212927",
      "123711891","1837212923","1837212925","123711873","2613066277","123696223",
      "123153901","123153941","6818460800","6818460799","6818460805","123015367",
      "123015369","123015371","6817275189","7861033574","6805824919","123120155",
      "4012726934","4012726933","67666150","7861033558","4060105092","4060105091",
      "4012726932","4012726929","7861033541","4060105090","4060105089","123120160",
      "122814232","122814235","122814237","122719192","123254964","1732340074","21302781",
      "7424313398","7424313397","7424313396","7424313395","7424313394","7424313393","4012759744",
      "4012759745","123280934","4012759746","4012759747","123292045","123292100","9591449436",
      "9591449432","9591449433","9591449434","9591449435","214470792","5472460620","4399914049",
      "4015405553","269633270","6820972462","4399914028","4015405552","6813411585","348121996",
      "4059993475","4399693649","4399693648","4015405549","1781230450","6820935898","7023424980",
      "1732243673","6813379489","4399693651","6814958456","1862347576","4540690065","4540705198",
      "4540705199","4540690064","4540761794"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Nekter Juice Bar to San Pedro Street
  path = m.CalculateShortestPath_Bellman_Ford("Nekter Juice Bar","San Pedro Street");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

//////////////////////////////////////////////////////////////////
TEST(TrojanMapStudentTest_13, CalculateShortestPath_Dijkstra) {
  TrojanMap m;
  
  // Test from "" to ""
  auto path = m.CalculateShortestPath_Dijkstra("", "");
  std::vector<std::string> gt{}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  // Reverse the input from "" to ""
  path = m.CalculateShortestPath_Dijkstra("", "");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

//////////////////////////////////////////////////////////////////
// Test CalculateShortestPath_Bellman_Ford function
TEST(TrojanMapStudentTest_14, CalculateShortestPath_Bellman_Ford) {
  TrojanMap m;
  // Test from "" to ""
  auto path = m.CalculateShortestPath_Bellman_Ford("", "");
  std::vector<std::string> gt{}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from "" to ""
  path = m.CalculateShortestPath_Bellman_Ford("", "");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

//////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_15, CalculateShortestPath_Dijkstra) {
  TrojanMap m;
  
  // Test from " " to " "
  auto path = m.CalculateShortestPath_Dijkstra(" ", " ");
  std::vector<std::string> gt{}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  // Reverse the input from "" to ""
  path = m.CalculateShortestPath_Dijkstra(" ", " ");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

//////////////////////////////////////////////////////////////////
// Test CalculateShortestPath_Bellman_Ford function
TEST(TrojanMapStudentTest_16, CalculateShortestPath_Bellman_Ford) {
  TrojanMap m;
  // Test from " Target" to "Chick-fil-A"
  auto path = m.CalculateShortestPath_Bellman_Ford(" ", " ");
  std::vector<std::string> gt{}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  
  path = m.CalculateShortestPath_Bellman_Ford(" ", " ");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}


//////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_17, CalculateShortestPath_Dijkstra) {
  TrojanMap m;
  
  // Test from " Target" to "Chick-fil-A"
  auto path = m.CalculateShortestPath_Dijkstra("Target", "Chick-fil-A");
  std::vector<std::string> gt{
    "5237417650","6814769289","6813379584","6813360961","6813379480",
    "6813360960","6814620882","6813360954","6813360952","6813379420",
    "6813360951","6813360936","6813379467","6813379466","6813379465",
    "6813379464","3402887075","6813379432","4536989637","4536989640",
    "3443310465","6813379491","6818390136","3433701978","4536989636",
    "3432332948","6814770351","3431300454","4536993735","6814770342",
    "2776870272","5580882852","6814770345","2776870269","1472141961",
    "5580883117","123153544","1673645147","2738332818","1673644724",
    "2738332817","122844997","5580881629","4399697303","4399697301",
    "4399697300","6813379550","6814916523","1732243620","4015372469",
    "4015372463","6819179749","1732243544","6813405275","348121996",
    "348121864","6813405280","1472141024","6813411590","216155217",
    "6813411589","1837212103","1837212101","6814916516","6814916515",
    "6820935910","4547476733" }; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  // Reverse the input 
  path = m.CalculateShortestPath_Dijkstra("Chick-fil-A", "Target");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}
//////////////////////////////////////////////////////////////////

// Test CalculateShortestPath_Bellman_Ford function
TEST(TrojanMapStudentTest_18, CalculateShortestPath_Bellman_Ford) {
  TrojanMap m;
  // Test from " " to " "
  auto path = m.CalculateShortestPath_Bellman_Ford("Target", "Chick-fil-A");
  std::vector<std::string> gt{
    "5237417650","6814769289","6813379584","6813360961","6813379480",
    "6813360960","6814620882","6813360954","6813360952","6813379420",
    "6813360951","6813360936","6813379467","6813379466","6813379465",
    "6813379464","3402887075","6813379432","4536989637","4536989640",
    "3443310465","6813379491","6818390136","3433701978","4536989636",
    "3432332948","6814770351","3431300454","4536993735","6814770342",
    "2776870272","5580882852","6814770345","2776870269","1472141961",
    "5580883117","123153544","1673645147","2738332818","1673644724",
    "2738332817","122844997","5580881629","4399697303","4399697301",
    "4399697300","6813379550","6814916523","1732243620","4015372469",
    "4015372463","6819179749","1732243544","6813405275","348121996",
    "348121864","6813405280","1472141024","6813411590","216155217",
    "6813411589","1837212103","1837212101","6814916516",
    "6814916515","6820935910","4547476733"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from " " to " "
  path = m.CalculateShortestPath_Bellman_Ford("Chick-fil-A", "Target");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

////////////////////////////////////////////////////////////////
// Test cycle detection function
TEST(TrojanMapStudentTest_19, CycleDetection) {
  TrojanMap m;
  
  // Test case 1
  std::vector<double> square1 = {0,0,0,0};
  auto sub1 = m.GetSubgraph(square1);
  bool result1 = m.CycleDetection(sub1, square1);
  EXPECT_EQ(result1, false);

  // Test case 2
  std::vector<double> square2 = {-118.300, -118.260, 34.010, 34.000};
  auto sub2 = m.GetSubgraph(square2);
  bool result2 = m.CycleDetection(sub2, square2);
  EXPECT_EQ(result2, true);
}

////////////////////////////////////////////////////////////////

// Test cycle detection function
TEST(TrojanMapStudentTest_20, CycleDetection) {
  TrojanMap m;
  
  std::vector<double> square2 = {-118.300, -118.270, 34.030, 34.010};
  auto sub2 = m.GetSubgraph(square2);
  bool result2 = m.CycleDetection(sub2, square2);
  EXPECT_EQ(result2, true);
}
//////////////////////////////////////////////////////////////////

// Test cycle detection function
TEST(TrojanMapStudentTest_21, CycleDetection) {
  TrojanMap m;
  
  // Test case 1
  std::vector<double> square1 = {0,0,0,0};
  auto sub1 = m.GetSubgraph(square1);
  bool result1 = m.CycleDetection(sub1, square1);
  EXPECT_EQ(result1, false);
}
//////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_22, TopologicalSort) {
  TrojanMap m;
  
  std::vector<std::string> location_names = {"Nekter Juice Bar", "Chipotle", "Chase", "Lululemon", "KFC"};
  std::vector<std::vector<std::string>> dependencies = {{"Chipotle","Nekter Juice Bar"}, {"Chipotle","Chase"}, {"Chipotle","Lululemon"}, {"Chipotle","KFC"}, {"Nekter Juice Bar","Chase"}, {"Nekter Juice Bar","Lululemon"}, {"Nekter Juice Bar","KFC"}, {"Chase","Lululemon"}, {"Chase","KFC"}, {"Lululemon","KFC"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Chipotle", "Nekter Juice Bar", "Chase", "Lululemon", "KFC"};
  EXPECT_EQ(result, gt);
}

//////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_23, TopologicalSort) {
  TrojanMap m;
  
  std::vector<std::string> location_names = {"Ralphs", "Chick-fil-A", "KFC"};
  std::vector<std::vector<std::string>> dependencies = {{"KFC","Ralphs"}, {"Ralphs","Chick-fil-A"}, {"Chick-fil-A","KFC"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={};
  EXPECT_EQ(result, gt);
}

//////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_24, TopologicalSort) {
  TrojanMap m;
  
  std::vector<std::string> location_names = {"Coffee Bean 1", "Cardinal Gardens", "CVS"};
  std::vector<std::vector<std::string>> dependencies = {{"Coffee Bean 1","Cardinal Gardens"}, {"CVS","Cardinal Gardens"}, {"CVS","Coffee Bean 1"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"CVS", "Coffee Bean 1", "Cardinal Gardens"};
  EXPECT_EQ(result, gt);
}
//////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_25, TSP3) {
  TrojanMap m;
  
  std::vector<std::string> input{"6808097023","123443150","123652221","6805827689","1855144910","8460910105"}; // Input location ids 
  auto result = m.TravellingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6808097023","123443150","6805827689","1855144910","8460910105","123652221","6808097023"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}

//////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_26, TSP3) {
  TrojanMap m;
  
  std::vector<std::string> input{"6808097023","123443150","123652221","6805827689","1855144910","8460910105"}; // Input location ids 
  auto result = m.TravellingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6808097023","123443150","6805827689","1855144910","8460910105","123652221","6808097023"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}


//////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_27, TSP3) {
  TrojanMap m;
  
  std::vector<std::string> input{"6808097023","123443150","123652221","6805827689","1855144910","8460910105"}; // Input location ids 
  auto result = m.TravellingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6808097023","123443150","6805827689","1855144910","8460910105","123652221","6808097023"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, false);
}

//////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_28, TSP3) {
  TrojanMap m;
  
  std::vector<std::string> input{"6693401461","4015486528","123367934","6278441216"}; // Input location ids 
  auto result = m.TravellingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6693401461","6278441216","4015486528","123367934","6693401461"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}

//////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_29, TSP3) {
  TrojanMap m;
  
  std::vector<std::string> input{"6693401461","4015486528","123367934","6278441216"}; // Input location ids 
  auto result = m.TravellingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6693401461","6278441216","4015486528","123367934","6693401461"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}


//////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_30, TSP3) {
  TrojanMap m;
  
  std::vector<std::string> input{"6693401461","4015486528","123367934","6278441216"}; // Input location ids 
  auto result = m.TravellingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6693401461","6278441216","4015486528","123367934","6693401461"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}

//////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_31, TSP3) {
  TrojanMap m;
  
  std::vector<std::string> input{"7281892638","932415999","8880155014","6793324081","6817252182"}; // Input location ids 
  auto result = m.TravellingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"7281892638","6793324081","8880155014","932415999","6817252182","7281892638"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}

//////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_32, TSP3) {
  TrojanMap m;
  
  std::vector<std::string> input{"7281892638","932415999","8880155014","6793324081","6817252182"}; // Input location ids 
  auto result = m.TravellingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"7281892638","6793324081","8880155014","932415999","6817252182","7281892638"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}


//////////////////////////////////////////////////////////////////

TEST(TrojanMapStudentTest_33, TSP3) {
  TrojanMap m;
  
  std::vector<std::string> input{"7281892638","932415999","8880155014","6793324081","6817252182"}; // Input location ids 
  auto result = m.TravellingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"7281892638","6793324081","8880155014","932415999","6817252182","7281892638"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}

//////////////////////////////////////////////////////////////////
// Test FindNearby points
TEST(TrojanMapStudentTest_34, FindNearby) {
  TrojanMap m;
  
  auto result = m.FindNearby("restaurant", "Ralphs", 20, 10);
  std::vector<std::string> ans{"6549779198", "7396326285", "5567727178", "6813379473", "5237417652", "2643391587", 
                                "5261316289", "5237417654", "9591449458", "4141781780"};
  EXPECT_EQ(result, ans);
}

//////////////////////////////////////////////////////////////////
// Test FindNearby points
TEST(TrojanMapStudentTest_35, FindNearby) {
  TrojanMap m;
  
  auto result = m.FindNearby("attraction", "Ralphs", 10, 10);
  std::vector<std::string> ans{"5229911604"};
  EXPECT_EQ(result, ans);
}
//////////////////////////////////////////////////////////////////
// Test FindNearby points
TEST(TrojanMapStudentTest_36, FindNearby) {
  TrojanMap m;
  
  auto result = m.FindNearby("cafe", "Chase", 30, 5);
  std::vector<std::string> ans{"614990288", "4089614984", "4162647227", "5261316290", "5567718696"};
  EXPECT_EQ(result, ans);
}