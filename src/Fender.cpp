//
// Created by arroganz on 11/26/17.
//

# include <string>
# include <iostream>
# include <experimental/filesystem>
# include "fender.hpp"
# include "sigCatch.hpp"
# include "goToBinDir.hpp"

extern "C" fender::Fender *Fender(std::string const &execPath) {
    return new fender::Fender(execPath);
}

static bool interrupt = false;

void onSigint(int)
{
  std::cout << "Interrupt signal received. Shutting down." << std::endl;
  interrupt = true;
}

fender::Fender::Fender(std::string const &arg0) {
    futils::goToBinDir(arg0);

    entityManager = std::make_unique<futils::EntityManager>();
    events = std::make_unique<futils::Mediator>();
    entityManager->provideMediator(*events);
    futils::SigHandler &sig = futils::SigHandler::inst();
    sig.set(SIGINT, onSigint);
}

void fender::Fender::loadSystemDir(std::string const &path, bool recursive, bool log)
{
    std::cout << "Loading all systems in " << path << std::endl;
    const auto fsPath = std::experimental::filesystem::path(path);
    for (auto & p : std::experimental::filesystem::directory_iterator(fsPath)) {
        if (log)
            std::cout << "-> Loading " << p << " from " << path << std::endl;
        if (recursive && std::experimental::filesystem::is_directory(p.path())) {
            if (log)
                std::cout << "--> Loading directory " << p.path() << std::endl;
            loadSystemDir(p.path(), recursive, log);
        }
        if (!std::experimental::filesystem::is_directory(p.path()))
            loadSystem(p.path());
    }
}

int fender::Fender::start(const StartParameters params) {
    this->loadSystemDir(params.configFilePath, params.recursive, params.logWhenLoading);
    const int numberOfSystems = entityManager->getNumberOfSystems();
    events->send<std::string>("Fender loaded " + std::to_string(numberOfSystems) + " systems.");
    return entityManager->run(); // this will init all systems
}

int fender::Fender::run() {
    int64_t runs = 0;
    events->send<std::string>("Fender running...");
    for (;entityManager->getNumberOfSystems() > 0; runs++) {
        if (entityManager->run() != 0 || interrupt)
            break ;
    }
    events->send<std::string>("Fender shutting down. Ran " + std::to_string(runs) + " times.");
    events->send<events::Shutdown>();
    entityManager->cleanSystems();
    return 0;
}
