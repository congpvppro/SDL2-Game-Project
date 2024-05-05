#include "platform.h"
#include <iostream>
#include <cmath>

int screenHeight = 800;
Platform::Platform(int index) {
    width = 100;
    height = 32;
    speed = 1;
    cnt = 0;
    x = rand() % 1300 + 20;
    y = 0 - height - (index * 170);

    int coinInt = rand() % 4;

    if (coinInt == 0 || index == 0)
        hasCoin = false;
    else
        hasCoin = true;

    coinX = (int)x + width / 2 - 24 / 2;
    coinY = (int)y - 24 - 5;
}

int Platform::getSpeed() {
    return speed;
}

double Platform::getX() {
    return x;
}

double Platform::getY() {
    return y;
}

int Platform::getWidth() {
    return width;
}

int Platform::getHeight() {
    return height;
}

bool Platform::getHasCoin() {
    return hasCoin;
}

void Platform::setHasCoin(bool value) {
    hasCoin = value;
}

int Platform::getCoinX() {
    return coinX;
}

int Platform::getCoinY() {
    return coinY;
}

void Platform::updatePosition(int &speed) {
    y += speed;

    coinX = (int)x + width / 2 - 24 / 2;
    coinY = (int)y - 24 - 5;

    if (y > screenHeight) {
        
        x = rand() % 1300 + 20;
        y = 0 - height - 900;
        cnt++;
        std::cout << cnt << std::endl;
        if (cnt > speed) speed ++;
        int coinInt = rand() % 4;

        if (coinInt == 0)
            hasCoin = false;
        else
            hasCoin = true;
    }
}