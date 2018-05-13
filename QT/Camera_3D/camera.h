#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include<QObject>
#include<QVector3D>
#include<QVector4D>
#include<QMatrix4x4>
#include<QtMath>
namespace LB
{
/*
     this is the coordinate be using

               ^ z
               |
               |
               |
               /----------> y
              /
             /
            V  x

*/


    class Camera:public QObject
    {
        Q_OBJECT
    public:
// pre_declare
        enum Direction{
            None=0,
            Up=1,
            Down=2,
            Left=3,
            Right=4,
            Front=5,
            Rear=6
        };
        Q_ENUMS(Direction)
// function
        Camera();
        virtual ~Camera(){}
        void setCameraPosition(QVector3D p);
        void setSpeedMove(float s);
        void setSpeedWaggle(float s);
        void setDirectionUp(QVector3D d);
        void setDirectionLook(QVector3D d);
        void setVerticalAngle(float a);
        void setAspectRatio(float a);
        void setNearPlane(float n);
        void setFarPlane(float f);
// operate function
        virtual void move(Direction d);
        virtual void waggle(Direction d);
        virtual void printInfo();   // Debug Method
// get status function
        QVector4D getCameraPosition() const;
        QVector4D getDirectionLook() const;
        QVector4D getDirectionUp() const;
        float getSpeedMove() const;
        float getSpeedWaggle() const;
        float getVerticalAngle() const;
        float getAspetRatio() const;
        float getNearPlane() const;
        float getFarPlane() const;
//  get matrix
        QMatrix4x4 getViewMatrix();
        QMatrix4x4 getViewMatrixLeftHand();
        QMatrix4x4 getProjectionMatrix();
    protected:
        QVector4D position;
        // the position of the free_camera

        QVector4D direction_look;
        //the look_direction

        QVector4D  direction_up;

        float speed_move;
        // the speed of camera moving

        float speed_waggle;
        // the speed of camera wagglling

        float vertical_angle;
        // angle of vertical field

        float aspect_ratio;
        // ration of width/height

        float near_plane;
        // the projection's near plane

        float far_plane;
        // the projection's far plane

    };





}
#endif // CAMERA_H
