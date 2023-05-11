#ifndef GAME_ENGINE_ENGINE_H
#define GAME_ENGINE_ENGINE_H


#include <memory>
#include <set>
#include <utility>

#include "engine/logging/Logger.h"
#include "engine/Stopwatch/Stopwatch.h"
#include "engine/resources/IResourceManager.h"
#include "engine/entity/components/view/IViewComponentCreator.h"
#include "engine/entity/components/audio/IAudioComponentCreator.h"
#include "engine/entity/Entity.h"
#include "engine/camera/Camera.h"
#include "engine/input/Input.h"
#include "engine/utils/FileReadSingleton.h"

namespace engine {

    /**
     * Interface class that represents the model and holds the data and logic of the game.
     * An instance of this class is used in a Renderer class.
     */
    class Engine {
    public:
        virtual ~Engine() = default;

        /**
         * Set quit flag.
         */
        void quit();

        /**
         * Check if the engine is quitting.
         * @return quit flag
         */
        bool isQuit() const;

        /**
         * Calls the sleepFrame function of Stopwatch singleton.
         */
        static void sleep();

        /**
         * Updates the physics simulation using a specified fixed delta time value
         * and updates the graphics using the variable delta time of Stopwatch.
         *
         * This allows the physics simulation to be completely deterministic, independent of the game's frame rate.
         *
         * Source: https://gafferongames.com/post/fix_your_timestep/
         */
        virtual void update();

        /**
         * Interface function that handles engine inputs.
         * @param inputs
         */
        virtual void handleInputs(const std::vector<Input> &inputs) = 0;

        /**
         * Updates the internal view project space of the camera and adjusts the positions and scale of the sidebars.
         * @param screen_x_min
         * @param screen_x_max
         * @param screen_y_min
         * @param screen_y_max
         */
        virtual void updateScreenResolution(float screen_x_min, float screen_x_max,
                                            float screen_y_min, float screen_y_max);

        const std::shared_ptr<IResourceManager> &getResourceManager() const;

        const std::shared_ptr<IViewComponentCreator> &getViewComponentCreator() const;

        const std::shared_ptr<IAudioComponentCreator> &getAudioComponentCreator() const;

        const std::shared_ptr<Camera> &getCamera() const;

    protected:
        /**
         * Interface constructor for a concrete game class.
         *
         * Loads resource data.
         * @param screen_x_min
         * @param screen_x_max
         * @param screen_y_min
         * @param screen_y_max
         * @param resource_manager
         * @param view_component_creator
         * @param audio_component_creator
         */
        Engine(float screen_x_min, float screen_x_max, float screen_y_min, float screen_y_max,
               std::shared_ptr<IResourceManager> resource_manager,
               std::shared_ptr<IViewComponentCreator> view_component_creator,
               std::shared_ptr<IAudioComponentCreator> audio_component_creator,
               std::shared_ptr<IFileReader> file_reader);

        std::shared_ptr<IResourceManager> _resource_manager;
        std::shared_ptr<IViewComponentCreator> _view_component_creator;
        std::shared_ptr<IAudioComponentCreator> _audio_component_creator;

        std::shared_ptr<Camera> _camera;

        std::shared_ptr<Entity> _sidebar1;
        std::shared_ptr<Entity> _sidebar2;

        /**
         * Initializes the two sidebar entities.
         * @param layer rendering layer
         */
        void initSidebars(unsigned int layer);

        /**
         * Interface function for graphics update.
         * @param t total time
         * @param dt delta time step
         */
        virtual void graphicsUpdate(double t, float dt);

        /**
         * Interface function for physics update.
         * @param t total time
         * @param dt delta time step
         */
        virtual void physicsUpdate(double t, float dt);

    private:
        bool _quit;

        float _physics_delta_time;
        double _physics_time;
        float _accumulator;
        float _physics_speed;
    };

} // engine

#endif //GAME_ENGINE_ENGINE_H
