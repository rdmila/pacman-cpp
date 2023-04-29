#pragma once
#include "../model/model.h"

class View {
    // Model& model;
public:
    virtual void show() = 0;
};

class ConsoleLogger : View {
public:
    void show();
};