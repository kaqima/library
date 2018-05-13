#include "camera.h"

LB::Camera::Camera():
    position(1.0f,0.0f,0.0f,1.0f),
    direction_look(-1.0f,0.0f,0.0f,0.0f),
    direction_up(0.0f,0.0f,1.0f,0.0f),
    speed_move(0.02f),
    speed_waggle(0.05f),
    vertical_angle(90),
    aspect_ratio(1.0f),
    near_plane(1.0f),
    far_plane(100.0f)
{}

void LB::Camera::setCameraPosition(QVector3D p)
{
    auto tem=p.toVector4D();
    tem.setW(1.0f);
    position=tem;
}

void LB::Camera::setSpeedMove(float s)
{
    speed_move=s;
}

void LB::Camera::setSpeedWaggle(float s)
{
    if(s<90&&s>0)
    speed_waggle=s;
    else
    {
        qDebug()<<"Error: can't set speed_waggle";
        qDebug()<<"Reason: speed_waggle you set  <=0 or >=90";
    }
}

void LB::Camera::setDirectionUp(QVector3D d)
{
    // new direction_up
    d.normalize();

    // direction_look
    auto d_look=direction_look.toVector3D();

    if(d==d_look||d==-d_look)
    {
        qDebug()<<"Error: set direction_up failed";
        qDebug()<<"Reason: direction_up you set is parallel to the direction_look";
        return;
    }
    else
    {
        // new direction_left
        auto d_left_n=QVector3D::crossProduct(d,d_look);

        // set direction_up
        auto up=QVector3D::crossProduct(d_look,d_left_n);
        up.normalize();
        direction_up=up.toVector4D();
    }
}

void LB::Camera::setDirectionLook(QVector3D d)
{
    // new direction_look
    d.normalize();

    // direction_look
    auto d_up=direction_up.toVector3D();

    if(d==d_up||d==-d_up)
    {
        qDebug()<<"Error: set Direction_look failed";
        qDebug()<<"Reason: Direction_look you set is Parallel to the Direction_up";
        return;
    }
    else
    {
       // set the direction_look
       direction_look=d.toVector4D();

       // set the direction_up
       auto d_left=QVector3D::crossProduct(d_up,d);
       auto up=QVector3D::crossProduct(d,d_left);
       up.normalize();
       direction_up=up.toVector4D();
    }
}

void LB::Camera::setVerticalAngle(float a)
{
    if(a>0&&a<180)
    vertical_angle=a;
    else
    {
        qDebug()<<"Error: fail to set Vertical Angle";
        qDebug()<<"Reason: value you set <= 0 or >= 180";
    }
}

void LB::Camera::setAspectRatio(float a)
{
    if(a>0||a*vertical_angle<180)
        aspect_ratio=a;
    else
    {
        qDebug()<<"Error: fail to set Aspect Angle";
        qDebug()<<"Reason: value you set <= 0 or (Vertical Angle * it >= 180_";
    }
    return;
}

void LB::Camera::setNearPlane(float n)
{
    if(n>0&&n<far_plane)
        near_plane=n;
    else
    {
        qDebug()<<"Error: fail to set Near Plane";
        qDebug()<<"Reason: value you set <=0 or >=far_plane";
    }
}

void LB::Camera::setFarPlane(float f)
{
    if(f>near_plane)
        far_plane=f;
    else
    {
        qDebug()<<"Error: fail to set Near Plane";
        qDebug()<<"Reason: value you set <=near_Plane";
    }
}

void LB::Camera::printInfo()
{
    qDebug()<<"----- Print Camera Info : -----";
    qDebug()<<" Camera Position :";
    qDebug()<<Camera::getCameraPosition();
    qDebug()<<" Camera Look Direction :";
    qDebug()<<Camera::getDirectionLook();
    qDebug()<<" Camera Up Direction :";
    qDebug()<<Camera::getDirectionUp();
    qDebug()<<"================================";
}

void LB::Camera::move(Camera::Direction d)
{
    QVector3D direction_left;
    switch (d) {
    case Camera::Up:
        position+=direction_up*speed_move;
        break;
    case Camera::Down:
        position-=direction_up*speed_move;
        break;
    case Camera::Left:
        direction_left=QVector3D::crossProduct(direction_up.toVector3D(),direction_look.toVector3D());
        direction_left.normalize();
        position+=direction_left*speed_move;
        break;
    case Camera::Right:
        direction_left=QVector3D::crossProduct(direction_up.toVector3D(),direction_look.toVector3D());
        direction_left.normalize();
        position-=direction_left*speed_move;
        break;
    case Camera::Front:
        position+=direction_look*speed_move;
        break;
    case Camera::Rear:
        position-=direction_look*speed_move;
        break;
    default:
        qDebug()<<"the direction you move is not set";
        break;
    }
}

void LB::Camera::waggle(Camera::Direction d)
{
    QMatrix4x4 matrix_rotate;
    QVector4D d_look;
    QVector3D direction_left;
    switch (d) {
    case Camera::Up:
        direction_left=QVector3D::crossProduct(direction_up.toVector3D(),direction_look.toVector3D());
        direction_left.normalize();
        matrix_rotate.rotate(-speed_waggle,direction_left);
        d_look=matrix_rotate*direction_look;
        setDirectionLook(d_look.toVector3D());
        break;
    case Camera::Down:
        direction_left=QVector3D::crossProduct(direction_up.toVector3D(),direction_look.toVector3D());
        direction_left.normalize();
        matrix_rotate.rotate(speed_waggle,direction_left);
        d_look=matrix_rotate*direction_look;
        setDirectionLook(d_look.toVector3D());
        break;
    case Camera::Left:
        matrix_rotate.rotate(speed_waggle,direction_up.toVector3D());
        d_look=matrix_rotate*direction_look;
        setDirectionLook(d_look.toVector3D());
        break;
    case Camera::Right:
        matrix_rotate.rotate(-speed_waggle,direction_up.toVector3D());
        d_look=matrix_rotate*direction_look;
        setDirectionLook(d_look.toVector3D());
        break;
    default:
        qDebug()<<"the direction you wggle is not set";
        break;
    }
}

QVector4D LB::Camera::getCameraPosition() const
{
    return position;
}

QVector4D LB::Camera::getDirectionLook() const
{
    return direction_look;
}

QVector4D LB::Camera::getDirectionUp() const
{
    return direction_up;
}

float LB::Camera::getSpeedMove() const
{
    return speed_move;
}

float LB::Camera::getSpeedWaggle() const
{
    return speed_waggle;
}

float LB::Camera::getVerticalAngle() const
{
    return vertical_angle;
}

float LB::Camera::getAspetRatio() const
{
    return aspect_ratio;
}

float LB::Camera::getNearPlane() const
{
    return near_plane;
}

float LB::Camera::getFarPlane() const
{
    return far_plane;
}

QMatrix4x4 LB::Camera::getProjectionMatrix()
{
    QMatrix4x4 matrix;
    matrix.perspective(vertical_angle,aspect_ratio,near_plane,far_plane);
    return matrix;
}

QMatrix4x4 LB::Camera::getViewMatrix()
{
    QMatrix4x4 matrix;
    matrix.lookAt(position.toVector3D(),(position+direction_look).toVector3D(),direction_up.toVector3D());
    return matrix;
}


QMatrix4x4 LB::Camera::getViewMatrixLeftHand()
{
    QVector3D p=position.toVector3D();
    QVector3D look=(position+direction_look).toVector3D();
    QVector3D up=direction_up.toVector3D();
    p.setZ(-p.z());
    look.setZ(-look.z());
    up.setZ(-up.z());
    QMatrix4x4 matrix;
    matrix.lookAt(p,look,up);
    return matrix;
}

