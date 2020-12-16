#ifndef TRAJECTORYPLANNER_H
#define TRAJECTORYPLANNER_H

#include <vector>
#include <algorithm>

class TrajectoryPlanner
{
public:
    // Constructor
    TrajectoryPlanner();

    // Public member variables
    bool m_isMoving;
    std::vector<double> m_startPosition;
    std::vector<double> m_targetPosition;
    int m_updateRateScaler;

    // Public methods
    void init(const std::vector<double> &startPosition, const std::vector<double> &targetPosition);
    std::vector<double> update();


private:
    // Private member variables
    long m_counter;
    std::vector<double> m_position;
    std::vector<double> m_positionScaler;

    // Private constants
    const int m_UPDATE_RATE_SCALER = 100;

};

#endif // TRAJECTORYPLANNER_H
