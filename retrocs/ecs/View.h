#pragma once

#include "../utils.h"
#include "VirtualScreen.h"

namespace retrocs::ecs
{
    template<typename Derived>
    struct View
    {
        int id;

        View(int _id = -1) : id(_id) {}

        void set_id(int _id) { id = _id; }

        template<typename D = Derived, typename... Args>
        auto init(VirtualScreen& screen_space, Args&&... args)
            -> typename std::enable_if_t<
                std::is_same_v<
                    decltype(std::declval<D>()._on_init(screen_space, std::forward<Args>(args)...)),
                    bool
                >,
                bool
            >
        {
            return static_cast<D*>(this)->_on_init(screen_space, std::forward<Args>(args)...);
        }

        virtual void populate_data(VirtualScreen& screen_space) {}
    };
}
