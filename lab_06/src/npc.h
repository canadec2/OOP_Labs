#pragma once
#include <string>
#include <memory>

class Visitor;

class NPC {
protected:
    double x, y;
    std::string name;
public:
    NPC(double x_, double y_, const std::string& name_) : x(x_), y(y_), name(name_) {}
    virtual ~NPC() {}
    virtual std::string getTypeName() const = 0;
    virtual void accept(Visitor& visitor) = 0;

    double getX() const { return x; }
    double getY() const { return y; }
    std::string getName() const { return name; }

    virtual bool canAttack(const NPC& other) const = 0;    // Логика: может ли атаковать другой тип
    virtual bool isDead() const = 0;                      // Пометка: мёртв ли
    virtual void attack(NPC& other) = 0;                 // Процесс атаки
    virtual void setDead(bool d) = 0;
};