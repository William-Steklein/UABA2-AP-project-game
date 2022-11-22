#ifndef GAME_ENGINE_ENTITYANIMATION_H
#define GAME_ENGINE_ENTITYANIMATION_H


#include <utility>

#include "engine/entities/components/IEntityComponent.h"
#include "engine/entities/components/IEntityView.h"
#include "engine/resources/Animation.h"
#include "engine/logging/Logger.h"

namespace engine {

    class EntityAnimation : public IEntityComponent {
    public:
        EntityAnimation(std::shared_ptr<AnimationGroup> animation_group);

        ~EntityAnimation() = default;

        void update(double t, float dt, Entity &entity) override;

        void setView(std::weak_ptr<IEntityView> view);

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
        std::shared_ptr<AnimationGroup> _animation_group;

        std::string _current_id;
        unsigned int _current_frame;
        float _current_time;
        bool _finished;
        bool _loop_finished;

        bool _loop;
        bool _mirror_h;
        bool _mirror_v;

        std::weak_ptr<IEntityView> _view;

        void changeView();
    };

} // engine

#endif //GAME_ENGINE_ENTITYANIMATION_H
