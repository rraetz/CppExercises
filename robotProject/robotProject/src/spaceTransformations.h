#ifndef SPACETRANSFORMATIONS_H
#define SPACETRANSFORMATIONS_H


#include <Geometry>
#include <String>

// TODO:
// - copy / move constructor
// - make rotating constructor safe


class Trans
{
public:
    Eigen::Affine3d m_T;

    // Constructor
    Trans() : m_T(Eigen::Affine3d::Identity()){}
    Trans(double x, double y, double z) : m_T(Eigen::Affine3d::Identity())
    {
        this->translate(x,y,z);
    }
    Trans(double angle, char type) : m_T(Eigen::Affine3d::Identity())
    {
        assert(type == 'x' || type == 'y' || type == 'z');
        switch(type)
        {
            case 'x': this->rotX(angle);
            case 'y': this->rotY(angle);
            case 'z': this->rotZ(angle);
        }
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
    Trans operator*(const Trans& T2)
    {
        Trans Tresult;
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
