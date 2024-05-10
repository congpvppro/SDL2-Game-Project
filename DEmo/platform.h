#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H
class Platform {
private:
    double x;
    double y;
    int width;
    int height;
    bool hasCoin;
    int coinX;
    int coinY;
    int speed;
    int cnt;
public:
    Platform(int index);
    int getSpeed();
    double getX();
    double getY();
    int getWidth();
    int getHeight();
    bool getHasCoin();
    void setHasCoin(bool value);
    int getCoinX();
    int getCoinY();
    void updatePosition(int &speed);
};
#endif