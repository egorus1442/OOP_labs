#pragma once
#include <coroutine>
#include <chrono>
#include <thread>
#include <vector>
#include "../npc/npc.h"
#include "thread_safe_container.h"
#include "../visitor/combat_visitor.h"

struct GameTask {
    struct promise_type {
        GameTask get_return_object() { 
            return GameTask{std::coroutine_handle<promise_type>::from_promise(*this)}; 
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };

    using handle_type = std::coroutine_handle<promise_type>;
    handle_type coro;

    explicit GameTask(handle_type h) : coro(h) {}
    
    ~GameTask() {
        if (coro) coro.destroy();
    }
    
    // Delete copy operations
    GameTask(const GameTask&) = delete;
    GameTask& operator=(const GameTask&) = delete;
    
    // Move operations
    GameTask(GameTask&& other) noexcept : coro(other.coro) {
        other.coro = nullptr;
    }
    
    GameTask& operator=(GameTask&& other) noexcept {
        if (this != &other) {
            if (coro) coro.destroy();
            coro = other.coro;
            other.coro = nullptr;
        }
        return *this;
    }
};

class CoroutineGame {
public:
    CoroutineGame();
    void start();
    void stop();

private:
    static constexpr int MAP_SIZE = 100;
    static constexpr int INITIAL_NPCS = 50;
    static constexpr int GAME_DURATION = 30;

    GameTask moveAndCombat();
    void processCombat(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender);
    void printMap();
    void initializeNPCs();
    int rollDice();

    ThreadSafeContainer npcs_;
    std::atomic<bool> running_{false};
    CombatVisitor combat_visitor_;
    GameTask game_task_{nullptr};
}; 