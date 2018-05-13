#pragma once
#ifndef FIXCAMERA_H
#define FIXCAMERA_H
#include <camera.h>

namespace LB
{
    class FixCamera: public Camera
    {
    public:
        FixCamera();
        FixCamera(QVector3D fixPosition);
        FixCamera(QVector3D fixPosition,QVector3D cameraPosition);
        virtual ~FixCamera(){}
        void setFixPosition(QVector3D p);

        // operate function
        virtual void move(Direction d);

        // get status function
        QVector4D getFixPosition() const;

    private:
        QVector4D fix_position;
    };
}
#endif // FIXCAMERA_H
