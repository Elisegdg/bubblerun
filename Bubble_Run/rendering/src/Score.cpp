#include <iostream>
#include <rendering/Score.hpp>
#include <fstream>

namespace rendering{

Score::Score()
{
    std::ifstream i("../Bubble_Run/assets/score.json");
    i >> m_array;
}

void Score::addScore(int score)
{
    std::ifstream i("../Bubble_Run/assets/score.json");
    i >> m_array;
    m_array["score"].push_back(score);
    std::sort(m_array["score"].rbegin(),m_array["score"].rend());
    std::ofstream o("../Bubble_Run/assets/score.json");
    o<<m_array;
}

}