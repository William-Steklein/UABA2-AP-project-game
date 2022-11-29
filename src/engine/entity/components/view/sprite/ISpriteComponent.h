#ifndef GAME_ENGINE_ISPRITECOMPONENT_H
#define GAME_ENGINE_ISPRITECOMPONENT_H


#include "engine/entity/components/view/IViewComponent.h"

namespace engine {

    class ISpriteComponent : public IViewComponent {
    public:
        ISpriteComponent(const Vector2f &size, std::weak_ptr<Camera> camera);

        ~ISpriteComponent() = default;

        virtual void setTexture(unsigned int texture_index);

        virtual void setTexture(unsigned int texture_index, bool mirror_h, bool mirror_v);

        bool isMirrorH() const;

        void setMirrorH(bool mirror_h);

        bool isMirrorV() const;

        void setMirrorV(bool mirror_v);

    protected:
        unsigned int _texture_index;
        bool _mirror_h;
        bool _mirror_v;

        virtual void updateSprite() = 0;
    };

} // engine

#endif //GAME_ENGINE_ISPRITECOMPONENT_H
