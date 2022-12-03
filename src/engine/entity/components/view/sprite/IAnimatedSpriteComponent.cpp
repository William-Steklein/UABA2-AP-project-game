#include "IAnimatedSpriteComponent.h"

namespace engine {
    IAnimatedSpriteComponent::IAnimatedSpriteComponent(const Vector2f &size, std::weak_ptr<Camera> camera,
                                                       bool project_ui_space)
            : ISpriteComponent(size, std::move(camera), project_ui_space),
              _current_id(""), _current_frame(0), _current_time(0),
              _loop(false), _finished(true), _loop_finished(false) {

    }

    void IAnimatedSpriteComponent::update(double t, float dt, Transform &transform) {
        if (_finished) return;

        bool update_view{false};

        _current_time += dt;
        while (_current_time >= _animation_group->animations[_current_id].frame_time) {
            _current_time -= _animation_group->animations[_current_id].frame_time;

            // if last frame of animation
            if (_current_frame == _animation_group->animations[_current_id].end_frame) {
                if (_loop) {
                    _current_frame = _animation_group->animations[_current_id].start_frame;
                    _loop_finished = true;
                    update_view = true;
                } else {
                    _finished = true;
                }
            } else {
                _current_frame += 1;
                update_view = true;
            }
        }

        if (update_view) setTexture(_current_frame, _mirror_h, _mirror_v);
    }

    void IAnimatedSpriteComponent::start(const std::string &animation_id, bool loop, bool mirror_h, bool mirror_v) {
        if (!_animation_group.get()) {
            throw std::runtime_error("An animation component has no animation data");
        } else if (_animation_group->animations.find(animation_id) == _animation_group->animations.end()) {
            throw std::runtime_error("An animation component has no animation \"" + animation_id + "\"");
        }

        _mirror_h = mirror_h;
        _mirror_v = mirror_v;

        _current_id = animation_id;
        _current_time = 0;
        _current_frame = _animation_group->animations[animation_id].start_frame;

        _loop = loop;
        _finished = false;
        _loop_finished = false;

        setTexture(_current_frame, _mirror_h, _mirror_v);
    }

    void IAnimatedSpriteComponent::setLoop(bool loop) {
        _loop = loop;
    }

    bool IAnimatedSpriteComponent::isFinished() const {
        return _finished;
    }

    bool IAnimatedSpriteComponent::isLoopFinished() {
        if (_loop_finished) {
            _loop_finished = false;
            return true;
        }
        return false;
    }

    void IAnimatedSpriteComponent::setAnimationGroup(std::shared_ptr<AnimationGroup> animation_group) {
        _animation_group = std::move(animation_group);
    }

    std::string IAnimatedSpriteComponent::getCurrentAnimationId() const {
        return _current_id;
    }
} // engine