#pragma once
#include "../model/model.h"

class Model;

class View {
protected:
     Model& model;
public:
    explicit View(Model&);
    virtual void update() = 0;
};

class ConsoleLogger : public View {
public:
    explicit ConsoleLogger(Model&);
    void update() override;
};