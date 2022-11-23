#include "AnimationComponent.h"

namespace engine {
    AnimationComponent::AnimationComponent(std::shared_ptr<AnimationGroup> animation_group)
            : _animation_group(std::move(animation_group)),
              _current_time(0),
              _loop(false), _mirror_h(false), _mirror_v(false),
              _finished(false), _loop_finished(false) {
        if (!_animation_group.get()) {
            throw std::runtime_error("An animation component has no animation group");
        } else if (_animation_group->animations.empty()) {
            throw std::runtime_error("An animation component has an empty animation group");
        }

        _current_id = _animation_group->animations.begin()->first;
        _current_frame = _animation_group->animations.begin()->second.start_frame;
    }

    void AnimationComponent::update(double t, float dt, Entity &entity) {
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

        if (update_view) updateViewTexture();
    }

    void AnimationComponent::setView(std::shared_ptr<IViewComponent> component) {
        _view = std::move(component);
        updateViewTexture();
    }

    std::shared_ptr<IViewComponent> AnimationComponent::getView() const {
        return _view;
    }

    void AnimationComponent::start(const std::string &animation_id, bool loop, bool mirror_h, bool mirror_v) {
        if (_animation_group->animations.find(animation_id) == _animation_group->animations.end()) {
            throw std::runtime_error("An animation component was unable to start animation \"" + animation_id + "\"");
        }

        _current_id = animation_id;
        _current_time = 0;
        _current_frame = _animation_group->animations[animation_id].start_frame;

        _loop = loop;
        _mirror_h = mirror_h;
        _mirror_v = mirror_v;
        _finished = false;
        _loop_finished = false;

        updateViewTexture();
    }

    void AnimationComponent::setLoop(bool loop) {
        _loop = loop;
    }

    bool AnimationComponent::getMirrorH() const {
        return _mirror_h;
    }

    void AnimationComponent::setMirrorH(bool mirror_h) {
        _mirror_h = mirror_h;
    }

    bool AnimationComponent::getMirrorV() const {
        return _mirror_v;
    }

    void AnimationComponent::setMirrorV(bool mirror_v) {
        _mirror_v = mirror_v;
    }

    bool AnimationComponent::isFinished() const {
        return _finished;
    }

    bool AnimationComponent::isLoopFinished() {
        if (_loop_finished) {
            _loop_finished = false;
            return true;
        }
        return false;
    }

    std::string AnimationComponent::getCurrentAnimationId() const {
        return _current_id;
    }

    void AnimationComponent::updateViewTexture() {
        if (_view.get()) {
            _view->setTexture(_current_frame, _mirror_h, _mirror_v);
        } else {
            throw std::runtime_error("An animation component with id \"" + _animation_group->id +
                                     "\" does not have a view component");
        }
    }
} // engine