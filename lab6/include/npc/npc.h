#pragma once
#include <string>
#include <memory>

class CombatVisitor;

class NPC {
public:
    virtual ~NPC() = default;
    
    virtual void accept(CombatVisitor& visitor) = 0;
    virtual bool isInRange(const NPC& other, double range) const;
    
    void setPosition(double x, double y);
    void setName(const std::string& name);
    
    double getX() const;
    double getY() const;
    std::string getName() const;
    virtual std::string getType() const = 0;

protected:
    double x_ = 0;
    double y_ = 0;
    std::string name_;
}; 