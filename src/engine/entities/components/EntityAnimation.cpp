#include "EntityAnimation.h"

namespace engine {

    EntityAnimation::EntityAnimation(std::shared_ptr<AnimationGroup> animation_group)
            : _animation_group(std::move(animation_group)),
              _current_time(0),
              _loop(false), _mirror_h(false), _mirror_v(false),
              _finished(false), _loop_finished(false) {
        if (!_animation_group.get()) {
            throw std::runtime_error("An EntityAnimation has no animation_group");
        } else if (_animation_group->animations.empty()) {
            throw std::runtime_error("An EntityAnimation has an empty animation_group");
        }

        _current_id = _animation_group->animations.begin()->first;
        _current_frame = _animation_group->animations.begin()->second.start_frame;
    }

    void EntityAnimation::update(double t, float dt, Entity &entity) {
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

    void EntityAnimation::setView(std::shared_ptr<IEntityView> view) {
        _view = std::move(view);
        updateViewTexture();
    }

    std::shared_ptr<IEntityView> EntityAnimation::getView() const {
        return _view;
    }

    void EntityAnimation::start(const std::string &animation_id, bool loop, bool mirror_h, bool mirror_v) {
        if (_animation_group->animations.find(animation_id) == _animation_group->animations.end()) {
            throw std::runtime_error("An EntityAnimation was unable to start animation \"" + animation_id + "\"");
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

    void EntityAnimation::setLoop(bool loop) {
        _loop = loop;
    }

    bool EntityAnimation::getMirrorH() const {
        return _mirror_h;
    }

    void EntityAnimation::setMirrorH(bool mirror_h) {
        _mirror_h = mirror_h;
    }

    bool EntityAnimation::getMirrorV() const {
        return _mirror_v;
    }

    void EntityAnimation::setMirrorV(bool mirror_v) {
        _mirror_v = mirror_v;
    }

    bool EntityAnimation::isFinished() const {
        return _finished;
    }

    bool EntityAnimation::isLoopFinished() {
        if (_loop_finished) {
            _loop_finished = false;
            return true;
        }
        return false;
    }

    std::string EntityAnimation::getCurrentAnimationId() const {
        return _current_id;
    }

    void EntityAnimation::updateViewTexture() {
        if (_view.get()) {
            _view->setTexture(_current_frame, _mirror_h, _mirror_v);
        } else {
            throw std::runtime_error("An EntityAnimation with animation_group_id \"" + _animation_group->id +
                                     "\" does not have an EntityView");
        }
    }

} // engine