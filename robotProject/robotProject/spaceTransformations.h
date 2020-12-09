#ifndef SPACETRANSFORMATIONS_H
#define SPACETRANSFORMATIONS_H

#include <Geometry>
#include <string>

// TODO:
// - copy / move constructor
// - make rotating constructor safe


class SE3
{
public:
    Eigen::Affine3d m_T;

    // Constructors
    SE3() : m_T(Eigen::Affine3d::Identity()){}

    // Constructor with pure translation
    SE3(double x, double y, double z) : m_T(Eigen::Affine3d::Identity())
    {
        this->translate(x,y,z);
    }

    // Constructor with pure rotation
    SE3(double angle, char type) : m_T(Eigen::Affine3d::Identity())
    {
        assert(type == 'x' || type == 'y' || type == 'z');
        switch(type)
        {
            case 'x': this->rotX(angle);
            case 'y': this->rotY(angle);
            case 'z': this->rotZ(angle);
        }
    }

    // Constructor using Denavit Hartenberg convention
    SE3(double theta, double d, double a, double alpha) : m_T(Eigen::Affine3d::Identity())
    {
        m_T.rotate(Eigen::AngleAxisd(theta, Eigen::Vector3d::UnitZ()));
        m_T.translate(Eigen::Vector3d(0,0,d));
        m_T.translate(Eigen::Vector3d(a,0,0));
        m_T.rotate(Eigen::AngleAxisd(alpha, Eigen::Vector3d::UnitX()));
    }




    // Translations
    void translate(double x, double y, double z)
    {
        m_T.translate(Eigen::Vector3d(x,y,z));
    }


    // Rotations
    void rotX(double angle)
    {
        m_T.rotate(Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitX()));
    }

    void rotY(double angle)
    {
        m_T.rotate(Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitY()));
    }

    void rotZ(double angle)
    {
        m_T.rotate(Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ()));
    }


    // Operator overload
    SE3 operator*(const SE3& T2)
    {
        SE3 Tresult;
        Tresult.m_T = m_T * T2.m_T;
        return Tresult;
    }


    // Print to String
    std::string printString()
    {
        std::string mat;
        for (int i = 0; i<4; ++i)
        {
            for (int j = 0; j<4; ++j)
            {
                mat.append(std::to_string(m_T(i,j)) + "\t");
            }
            mat.append("\n");
        }
        return mat;
    }
};

#endif // SPACETRANSFORMATIONS_H
