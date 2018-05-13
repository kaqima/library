#include "fixcamera.h"


LB::FixCamera::FixCamera()
{
    Camera::Camera();
    fix_position=QVector4D(0.0f,0.0f,0.0f,1.0f);
}

LB::FixCamera::FixCamera(QVector3D fixPosition)
{
    FixCamera();
    if(fixPosition!=position.toVector3D())
    {
        Camera::setCameraPosition(position.toVector3D());
        Camera::setDirectionLook(fixPosition-position.toVector3D());
    }
    else
    {
        qDebug()<<"Error: can't set fix position";
        qDebug()<<"Reason: fix position you set is same to camera position";
    }
}

LB::FixCamera::FixCamera(QVector3D fixPosition, QVector3D cameraPosition)
{
    FixCamera();
    if(fixPosition!=cameraPosition)
    {
        position=cameraPosition;
        fix_position=fixPosition;
        setDirectionLook(fixPosition-position.toVector3D());
    }
    else
    {
        qDebug()<<"Error: can't set fix position";
        qDebug()<<"Reason: fix position you set is same to camera position";
    }
}

void LB::FixCamera::setFixPosition(QVector3D p)
{
    if(fix_position!=position)
    {
        fix_position=p;
        Camera::setDirectionLook(getFixPosition().toVector3D()-p);
        Camera::setDirectionUp(QVector3D(0.0f,0.0f,1.0f));
    }
    else
    {
        qDebug()<<"Error: can't set fix position";
        qDebug()<<"Reason: fix position you set is same to camera position";
    }
}


void LB::FixCamera::move(Camera::Direction d)
{
    QVector4D p;
    QVector4D t;
    QMatrix4x4 r;
    double distance=position.toVector3D().distanceToPoint(fix_position.toVector3D());
    float a;

    switch (d)
    {
    case Camera::Up:
        a=qRadiansToDegrees(qAsin(-Camera::getDirectionLook().z()));

        if(a+speed_waggle>=90)
            return;
        else
        {
            Camera::waggle(Camera::Down);
            Camera::setCameraPosition((getFixPosition()-Camera::getDirectionLook()*distance).toVector3D());
        }
        break;
    case Camera::Down:
        a=qRadiansToDegrees(qAsin(-Camera::getDirectionLook().z()));

        if(a-speed_waggle<=-90)
            return;
        else
        {
            Camera::waggle(Camera::Up);
            Camera::setCameraPosition((getFixPosition()-Camera::getDirectionLook()*distance).toVector3D());
        }
        break;
    case Camera::Left:
        p=Camera::getCameraPosition()-getFixPosition();
        r.rotate(-speed_waggle,QVector3D(0.0f,0.0f,1.0f));
        t=r*p;
        Camera::setCameraPosition((t+getFixPosition()).toVector3D());
        Camera::setDirectionLook((getFixPosition()-position).toVector3D());
        Camera::setDirectionUp(QVector3D(0.0f,0.0f,1.0f));

        break;
    case Camera::Right:
        p=Camera::getCameraPosition()-getFixPosition();
        r.rotate(speed_waggle,QVector3D(0.0f,0.0f,1.0f));
        t=r*p;
        Camera::setCameraPosition((t+getFixPosition()).toVector3D());
        Camera::setDirectionLook((getFixPosition()-position).toVector3D());
        Camera::setDirectionUp(QVector3D(0.0f,0.0f,1.0f));

        break;
    case Camera::Front:
        if(distance-speed_move<=0)
            return;
        else
            Camera::move(Camera::Front);
        break;
    case Camera::Rear:
        Camera::move(Camera::Rear);
        break;
    default:
        qDebug()<<"the direction you move is not set";
        break;
    }
}

QVector4D LB::FixCamera::getFixPosition() const
{
    return fix_position;
}
