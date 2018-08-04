//
// Created by arroganz on 1/12/18.
//

#pragma once

# include "fender.hpp"
# include "Components/ListView.hpp"

namespace fender::entities {
    class ListView : public GameObject {
    protected:
        components::ListView *_list{nullptr};
    public:
        ListView(int size = -1) {
            _list = &attach<components::ListView>();
            _list->size = size;
        }
        virtual ~ListView()
        {
            // This code is debatable ! Maybe the ownership should not be within ListView ?
            for (auto elem: _list->content)
            {
                entityManager->destroy(*elem);
            }
            detach<components::ListView>();
        }
    };
}

