#pragma once

#include <vector>

enum class Alignment {
    VERTICAL, HORIZONTAL
};

enum class Direction {
    UP = 1, RIGHT = 2, DOWN = -1, LEFT = -2, NONE = 0
};

struct Shift {
    int y;
    int x;
};

Shift GetShift(Direction);
Direction GetDirection(Shift);
Direction ReverseDirection(Direction dir);

struct Cell {
    static const int width = 100;

    int y;
    int x;
    bool operator==(const Cell &) const;
    bool operator!=(const Cell &) const;
    Cell& operator+=(const Shift &);
    Cell& operator*=(int scale);
};

Shift operator-(const Cell &first, const Cell &second);

struct Edge {
    static const int length = Cell::width;

    Cell first;
    Cell second;

    // Alignment getAlignment();
};

struct Position {
    Edge edge;
    int shift;
    void reverse();
    Cell GetCell() const;
};

Cell PositionOnCanvas(const Position &pos);

class PositionOwner {
public:
    virtual Position GetPosition() = 0;
};

class GhostCollision {
};

class GameOver {
};

template<typename E>
class Observer {
public:
    virtual void HandleEvent(E);
};

template<typename E>
void Observer<E>::HandleEvent(E) {}

template<typename E>
class EventManager {
    std::vector<Observer<E>*> observers;
public:
    EventManager() = default;
    void AddObserver(Observer<E>*);
    void SendEvent(E);
};

template<typename E>
void EventManager<E>::SendEvent(E event) {
    for (Observer<E>* observer : observers) {
        observer->HandleEvent(event);
    }
}

template<typename E>
void EventManager<E>::AddObserver(Observer<E>* observer) {
    observers.push_back(observer);
}