#pragma once

#include "../Utils.h"

#include "View.h"

namespace retrocs
{
    namespace ecs
    {
        struct entity_view : view
        {
            vector<float>& X;
            vector<float>& Y;
            
            entity_view(int _id, vector<float>& _X, vector<float>& _Y) : view(_id), X(_X), Y(_Y) {}

            float x() const { return X[id]; }
            float y() const { return Y[id]; }
        };
    }
}