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
    void init(const std::vector<double> &startPosition, const std::vector<double> &targetPosition)
    {
        // Reset member variables
        m_startPosition = startPosition;
        m_targetPosition = targetPosition;
        m_position = m_startPosition;
        m_counter = 0;
        m_positionScaler.clear();

        // Compute position differences, wrap angles and set positionScaler accordingly
        auto diffLambda ([](double start, double end)
        {
            if (end-start > 180) {return end-start-360;}
            else if(end-start < -180) {return 360-start+end;}
            else {return end-start;}
        });
        std::transform(m_startPosition.begin(), m_startPosition.end(),
                       m_targetPosition.begin(), std::back_inserter(m_positionScaler), diffLambda);
    }


    // Returns vector with updated positions
    std::vector<double> update()
    {
        m_isMoving = static_cast<double>(m_counter)/m_updateRateScaler <= 1;
        if (m_isMoving)
        {
            ++m_counter;
            for (size_t i=0; i<m_position.size(); ++i)
            {
                m_position.at(i) = m_startPosition.at(i)  +
                        0.5*(1.0 + std::sin(M_PI*static_cast<double>(m_counter)/m_updateRateScaler - M_PI_2))*m_positionScaler.at(i);
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
