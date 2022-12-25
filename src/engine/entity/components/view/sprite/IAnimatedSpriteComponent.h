#ifndef GAME_ENGINE_IANIMATEDSPRITECOMPONENT_H
#define GAME_ENGINE_IANIMATEDSPRITECOMPONENT_H


#include <utility>

#include "engine/entity/components/view/sprite/ISpriteComponent.h"
#include "engine/resources/Animation.h"
#include "engine/logging/Logger.h"

namespace engine {

    class IAnimatedSpriteComponent : public ISpriteComponent {
    public:
        IAnimatedSpriteComponent(const Vector2f &size, std::weak_ptr<Camera> camera, bool project_ui_space);

        ~IAnimatedSpriteComponent() = default;

        void update(double t, float dt) override;

        void start(const std::string &animation_id, bool loop);

        void start(const std::string &animation_id, bool loop, bool mirror_h, bool mirror_v);

        void setLoop(bool loop);

        bool isFinished() const;

        bool isLoopFinished();

        void setAnimationGroup(std::shared_ptr<AnimationGroup> animation_group);

        std::string getCurrentAnimationId() const;

    private:
        std::shared_ptr<AnimationGroup> _animation_group;

        std::string _current_id;
        unsigned int _current_frame;
        float _current_time;

        bool _loop;
        bool _finished;
        bool _loop_finished;
    };

} // engine

#endif //GAME_ENGINE_IANIMATEDSPRITECOMPONENT_H
