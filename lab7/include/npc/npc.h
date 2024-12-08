#pragma once
#include <string>
#include <memory>
#include <atomic>

class CombatVisitor;

class NPC {
public:
    virtual ~NPC() = default;
    
    virtual void accept(CombatVisitor& visitor) = 0;
    virtual bool isInRange(const NPC& other) const;
    
    void setPosition(double x, double y);
    void setName(const std::string& name);
    void kill() { is_dead_ = true; }
    
    double getX() const;
    double getY() const;
    std::string getName() const;
    virtual std::string getType() const = 0;
    bool isDead() const { return is_dead_; }
    
    virtual double getMoveSpeed() const = 0;
    virtual double getCombatDistance() const = 0;

protected:
    double x_ = 0;
    double y_ = 0;
    std::string name_;
    std::atomic<bool> is_dead_{false};
}; 