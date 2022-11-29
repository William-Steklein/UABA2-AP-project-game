#ifndef GAME_ENGINE_ENGINE_H
#define GAME_ENGINE_ENGINE_H


#include <memory>
#include <set>
#include <utility>

#include "engine/logging/Logger.h"
#include "engine/Stopwatch.h"
#include "engine/resources/IResourceManager.h"
#include "engine/entity/components/view/IViewComponentCreator.h"
#include "engine/entity/components/audio/IAudioComponentCreator.h"
#include "engine/entity/Entity.h"
#include "engine/camera/Camera.h"
#include "engine/Input.h"

namespace engine {

    class Engine {
    public:
        Engine(float screen_x_min, float screen_x_max, float screen_y_min, float screen_y_max,
               std::shared_ptr<IResourceManager> resource_manager,
               std::shared_ptr<IViewComponentCreator> view_component_creator,
               std::shared_ptr<IAudioComponentCreator> audio_component_creator);

        ~Engine();

        static void sleep();

        virtual void update();

        virtual void handleInputs(const std::vector<Input> &inputs) = 0;

        virtual void updateScreenResolution(float screen_x_min, float screen_x_max,
                                            float screen_y_min, float screen_y_max);

        const std::shared_ptr<IResourceManager> &getResourceManager() const;

        const std::shared_ptr<IViewComponentCreator> &getViewComponentCreator() const;

        const std::shared_ptr<IAudioComponentCreator> &getAudioComponentCreator() const;

        const std::shared_ptr<Camera> &getCamera() const;

    protected:
        std::shared_ptr<IResourceManager> _resource_manager;
        std::shared_ptr<IViewComponentCreator> _view_component_creator;
        std::shared_ptr<IAudioComponentCreator> _audio_component_creator;

        std::shared_ptr<Camera> _camera;

        std::shared_ptr<Entity> _sidebar1;
        std::shared_ptr<Entity> _sidebar2;

        void initSidebars();

        virtual void update(double t, float dt);

        virtual void physicsUpdate(double t, float dt);

    private:
        float _physics_delta_time;
        double _physics_time;
        float _accumulator;
        float _physics_speed;
    };

} // engine

#endif //GAME_ENGINE_ENGINE_H
