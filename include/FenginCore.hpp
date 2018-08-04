#ifndef FENDER_LIBRARY_H
#define FENDER_LIBRARY_H

# include <iostream>
# include <string>
# include <memory>
# include <functional>
# include <stack>
# include <map>
# include "futils.hpp"
# include "types.hpp"
# include "dloader.hpp"
# include "ecs.hpp"
# include "mediator.hpp"
# include "events.hpp"
# include "rendering.hpp"

// Utils forward declarations
namespace futils
{
    class Dloader;
    class Ini;
}

namespace fengin
{
    using vec2f = futils::Vec2<float>;
    using vec3f = futils::Vec3<float>;
    using vec2i = futils::Vec2<int>;
    using vec3i = futils::Vec3<int>;
    using vec2ui = futils::Vec2<unsigned int>;
    using vec3ui = futils::Vec3<unsigned int>;

    struct StartParameters {
        std::string configFilePath;
        bool recursive = false;
        bool logWhenLoading = true;
    };

    class FenginCore
    {
        futils::UP<futils::EntityManager> core;
        futils::UP<futils::Mediator> events;
    public:
        explicit FenginCore(std::string const &);
        int start(StartParameters params);
        int run();

        void loadSystemDir(std::string const &path, bool recursive, bool log);

        template <typename ...Args>
        futils::LoadStatus loadSystem(std::string const &path, Args... args)
        {
            return core->loadSystem(path, args...);
        };

        template <typename System, typename ...Args>
        void addSystem(Args ...args) {
            core->addSystem<System>(args...);
        };

        template <typename System>
        void addSystem()
        {
            core->addSystem<System>();
        }

        template <typename System>
        void removeSystem() {
            core->removeSystem(futils::demangle<System>());
        }

        template <typename T, typename ...Args>
        T *createEntity(Args ...args) {
            return core->create<T>(args...);
        };
    };
}

#endif
