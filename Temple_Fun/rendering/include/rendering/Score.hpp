#ifndef _SCORE_HPP
#define _SCORE_HPP

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
    ~Score()=default;
    void addScore(int sccore);
    json getArray(){return m_array;}
    
};

#endif