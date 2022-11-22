#ifndef GAME_ENGINE_IENTITYVIEW_H
#define GAME_ENGINE_IENTITYVIEW_H


#include "engine/entities/components/IEntityComponent.h"
#include "engine/math/Vector2f.h"

namespace engine {

    class IEntityView : public IEntityComponent {
    public:
        IEntityView();

        void update(double t, float dt, Entity &entity) override = 0;

        virtual void setTexture(unsigned int texture_index, bool mirror_h, bool mirror_v);

    protected:
        Vector2f _size;

        unsigned int _texture_index;
        bool _mirror_h;
        bool _mirror_v;
    };

} // engine

#endif //GAME_ENGINE_IENTITYVIEW_H
