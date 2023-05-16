#pragma once

#include <vector>
#include <cstddef>

enum class Direction {
    UP = 1, RIGHT = 2, DOWN = -1, LEFT = -2, NONE = 0
};

struct Shift {
    int y;
    int x;
};

struct Point {
    float y;
    float x;
    Point& operator-=(const Point&);
    Point& operator+=(const Point&);
    Point& operator*=(float);
    Point& operator/=(float);
    Point operator*(float) const;
    Point operator/(float) const;
    float magnitude_sqr() const;
};

Point operator-(const Point&, const Point&);
Point operator+(const Point&, const Point&);

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

    Cell() = default;
    Cell(int y, int x);
};

Cell operator+(const Cell&, const Shift&);
Shift operator-(const Cell&, const Cell&);

struct Edge {
    static const int length = Cell::width;

    Cell from;
    Cell to;

    Edge() = default;
    Edge(Cell, Cell);
    Edge(Cell, Direction);
};

struct Position {
    Edge edge;
    int shift;
    void reverse();
    Cell GetCell() const;

    Position() = default;
    Position(Edge, int);
    Position(Cell, Direction);
};

Point PositionOnCanvas(const Cell& cell);
Point PositionOnCanvas(const Position& pos);

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