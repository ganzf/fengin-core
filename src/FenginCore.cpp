//
// Created by arroganz on 11/26/17.
//

# include <string>
# include <iostream>
# include <experimental/filesystem>
# include "FenginCore.hpp"
# include "utils/sigCatch.hpp"
# include "utils/goToBinDir.hpp"

extern "C" fengin::FenginCore *FenginCore(std::string const &execPath) {
    return new fengin::FenginCore(execPath);
}

static bool interrupt = false;

void onSigint(int)
{
  std::cout << "Interrupt signal received. Shutting down." << std::endl;
  interrupt = true;
}

namespace fengin {
    FenginCore::FenginCore(std::string const &arg0){
        futils::goToBinDir(arg0);

        core = std::make_unique<futils::EntityManager>();
        events = std::make_unique<futils::Mediator>();
        core->provideMediator(*events);
        futils::SigHandler &sig = futils::SigHandler::inst();
        sig.set(SIGINT, onSigint);
    }

    void fengin::FenginCore::loadSystemDir(std::string const &path, bool recursive, bool log, bool loadSymlinks)
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
            if (!std::experimental::filesystem::is_directory(p.path())) {
                const bool isSymlink = std::experimental::filesystem::is_symlink(p.path());
                if ((loadSymlinks && isSymlink) || !isSymlink)
                    loadSystem(p.path());
            }
        }
    }

    int fengin::FenginCore::start(const StartParameters params) {
        this->loadSystemDir(params.configFilePath, params.recursive, params.logWhenLoading);
        const int numberOfSystems = core->getNumberOfSystems();
        events->send<std::string>("Fender loaded " + std::to_string(numberOfSystems) + " systems.");
        return core->run(); // this will init all systems
    }

    int fengin::FenginCore::run() {
        int64_t runs = 0;
        events->send<std::string>("Fender running...");
        for (;core->getNumberOfSystems() > 0; runs++) {
            if (core->run() != 0 || interrupt)
                break ;
        }
        events->send<std::string>("Fender shutting down. Ran " + std::to_string(runs) + " times.");
        events->send<events::Shutdown>();
        core->cleanSystems();
        return 0;
    }
}