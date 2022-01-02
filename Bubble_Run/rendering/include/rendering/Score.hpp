/**
 * \file Score.hpp
 * \brief Declaration of the class Score
*/

#ifndef _SCORE_HPP
#define _SCORE_HPP

#include <vector>
#include "../include/rendering/json.hpp"
using json = nlohmann::json;

namespace rendering{
/*! \class Score
   * \brief Class of Score
   *
   *  This class enables to manage the score and save them
   */
class Score
{
private:
    std::vector<int> m_vecscore; /*!< Vector that contains the scores saved*/
    json m_array; /*!< Array that stores the data of the .json */
public:

    /*!
    *  \brief Default Constructor of the Score class
    */
    Score();

    /*!
    *  \brief Destructor of the Score class
    */
    ~Score()=default;

    /*!
    *  \brief Saves the score in the vector m_vecscore
    *  \param score Score that we want to save
    */
    void addScore(int score);

    /*!
    *  \brief Getter of the data of the .json
    */
    json getArray(){return m_array;}
    
};

}

#endif