//
// Created by arroganz on 12/16/17.
//

#include <events.hpp>
#include "Log.hpp"

extern "C" futils::ISystem *build()
{
    return new Log();
}

Log::Log()
{
    name = "Log";
}

void Log::init() {
    phase++;
    events->require<std::string>
            (this,
             [this](futils::IMediatorPacket &pkg) {
        auto &s = futils::Mediator::rebuild<std::string>(pkg);
        std::cout << "--> \t" << s << std::endl;
    });
    addReaction<events::Shutdown>([this](futils::IMediatorPacket &){
       entityManager->removeSystem(name);
    });
}

void Log::run(float)
{
    switch (phase) {
        case 0: return init();
    }
}