#pragma one
#include <vector>
#include "../include/rendering/json.hpp"
using json = nlohmann::json;

class Score
{
private:
    std::vector<int> m_vecscore;
    json m_array;
    int first;
public:
    Score();
    void addScore(int sccore);
    json getArray(){return m_array;}
    
};

// //read
//     std::ifstream i("../Temple_Fun/assets/score.json");
//     json j;
//     i >> j;

//     //int first = j["list"][0];

//     //write
//     std::vector<int> vecint;
    
//     json array;
//     array["list"] = {vecint};
//     std::ofstream o("../Temple_Fun/assets/score.json");
//     o<<array;

