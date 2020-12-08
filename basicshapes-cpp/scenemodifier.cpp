/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "scenemodifier.h"

#include <QtCore/QDebug>

SceneModifier::SceneModifier(Qt3DCore::QEntity *rootEntity)
    : m_rootEntity(rootEntity)
{

    // Torus shape data
    //! [0]
    m_torus = new Qt3DExtras::QTorusMesh();
    m_torus->setRadius(1.0f);
    m_torus->setMinorRadius(0.4f);
    m_torus->setRings(100);
    m_torus->setSlices(20);
    //! [0]

    // TorusMesh Transform
    //! [1]
    Qt3DCore::QTransform *torusTransform = new Qt3DCore::QTransform();
    torusTransform->setScale(2.0f);
    torusTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 25.0f));
    torusTransform->setTranslation(QVector3D(5.0f, 4.0f, 0.0f));
    //! [1]

    //! [2]
    Qt3DExtras::QPhongMaterial *torusMaterial = new Qt3DExtras::QPhongMaterial();
    torusMaterial->setDiffuse(QColor(QRgb(0xbeb32b)));
    //! [2]

    // Torus
    //! [3]
    m_torusEntity = new Qt3DCore::QEntity(m_rootEntity);
    m_torusEntity->addComponent(m_torus);
    m_torusEntity->addComponent(torusMaterial);
    m_torusEntity->addComponent(torusTransform);
    //! [3]


    // Cylinder shape data
    Qt3DExtras::QCylinderMesh *cylinder = new Qt3DExtras::QCylinderMesh();
    cylinder->setRadius(1);
    cylinder->setLength(3);
    cylinder->setRings(100);
    cylinder->setSlices(20);

    // CylinderMesh Transform
    Qt3DCore::QTransform *cylinderTransform = new Qt3DCore::QTransform();
    cylinderTransform->setScale(1.5f);
    cylinderTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 45.0f));
    cylinderTransform->setTranslation(QVector3D(-5.0f, 4.0f, -1.5));

    Qt3DExtras::QPhongMaterial *cylinderMaterial = new Qt3DExtras::QPhongMaterial();
    cylinderMaterial->setDiffuse(QColor(QRgb(0x928327)));

    // Cylinder
    m_cylinderEntity = new Qt3DCore::QEntity(m_rootEntity);
    m_cylinderEntity->addComponent(cylinder);
    m_cylinderEntity->addComponent(cylinderMaterial);
    m_cylinderEntity->addComponent(cylinderTransform);



}

SceneModifier::~SceneModifier()
{
}

//! [4]
void SceneModifier::enableTorus(bool enabled)
{
    m_torusEntity->setEnabled(enabled);
}
//! [4]

void SceneModifier::enableCylinder(bool enabled)
{
    m_cylinderEntity->setEnabled(enabled);
}


