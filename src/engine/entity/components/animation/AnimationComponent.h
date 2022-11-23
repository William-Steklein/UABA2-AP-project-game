#ifndef GAME_ENGINE_ANIMATIONCOMPONENT_H
#define GAME_ENGINE_ANIMATIONCOMPONENT_H


#include <utility>

#include "engine/entity/components/IComponent.h"
#include "engine/entity/components/view/IViewComponent.h"
#include "engine/resources/Animation.h"
#include "engine/logging/Logger.h"

namespace engine {

    class AnimationComponent : public IComponent {
    public:
        AnimationComponent(std::shared_ptr<AnimationGroup> animation_group);

        ~AnimationComponent() = default;

        void update(double t, float dt, Entity &entity) override;

        void setView(std::shared_ptr<IViewComponent> component);

        std::shared_ptr<IViewComponent> getView() const;

        void start(const std::string &animation_id, bool loop, bool mirror_h, bool mirror_v);

        void setLoop(bool loop);

        bool getMirrorH() const;

        void setMirrorH(bool mirror_h);

        bool getMirrorV() const;

        void setMirrorV(bool mirror_v);

        bool isFinished() const;

        bool isLoopFinished();

        std::string getCurrentAnimationId() const;

    private:
        std::shared_ptr<IViewComponent> _view;
        std::shared_ptr<AnimationGroup> _animation_group;

        std::string _current_id;
        unsigned int _current_frame;
        float _current_time;
        bool _finished;
        bool _loop_finished;

        bool _loop;
        bool _mirror_h;
        bool _mirror_v;

        void updateViewTexture();
    };

} // engine

#endif //GAME_ENGINE_ANIMATIONCOMPONENT_H
