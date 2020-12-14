#ifndef TRAJECTORYPLANNER_H
#define TRAJECTORYPLANNER_H

#include <vector>
#include <algorithm>

class TrajectoryPlanner
{
public:

    TrajectoryPlanner();
    ~TrajectoryPlanner(){}

    bool m_isMoving;
    std::vector<double> m_startPosition;
    std::vector<double> m_targetPosition;
    int m_updateRateScaler;


    void init(const std::vector<double> &startPosition, const std::vector<double> &targetPosition);
    std::vector<double> update();


private:
    long m_counter;
    std::vector<double> m_position;
    std::vector<double> m_positionScaler;

};

#endif // TRAJECTORYPLANNER_H
