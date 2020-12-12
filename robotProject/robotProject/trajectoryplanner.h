#ifndef TRAJECTORYPLANNER_H
#define TRAJECTORYPLANNER_H

#include <math.h>
#include <vector>
#include <algorithm>


class TrajectoryPlanner
{
public:

    TrajectoryPlanner()
        : m_isMoving(false)
        , m_updateRateScaler(100)
        , m_counter(0)
    {}

    ~TrajectoryPlanner(){}

    bool m_isMoving;
    std::vector<double> m_startPosition;
    std::vector<double> m_targetPosition;
    int m_updateRateScaler;


    // Prepares the trajectory planner for the next movement
    void init(std::vector<double> startPosition, std::vector<double> & targetPosition)
    {
        // Reset member variables
        m_startPosition = startPosition;
        m_targetPosition = targetPosition;
        m_position = m_startPosition;
        m_counter = 0;
        m_positionScaler.clear();

        // Compute position differences and set positionScaler accordingly
        std::transform(m_startPosition.begin(), m_startPosition.end(),
                       m_targetPosition.begin(),
                       std::back_inserter(m_positionScaler),
                       [](double start, double end) {return end-start; });
    }


    // Returns vector with updated positions
    std::vector<double> update()
    {
        m_isMoving = m_counter/(double)m_updateRateScaler <= 1;
        if (m_isMoving)
        {
            ++m_counter;
            for (size_t i=0; i<m_position.size(); ++i)
            {
                m_position.at(i) = m_startPosition.at(i)  +
                        0.5*(1 + std::sin(M_PI*m_counter/(double)m_updateRateScaler  - M_PI_2))*m_positionScaler.at(i);
            }
        }
        return m_position;
    }


private:
    long m_counter;
    std::vector<double> m_position;
    std::vector<double> m_positionScaler;


};

#endif // TRAJECTORYPLANNER_H
