#ifndef GAME_ENGINE_IOBSERVER_H
#define GAME_ENGINE_IOBSERVER_H

namespace engine {

    class IObserver {
    public:
        virtual void handleEvent() = 0;

        virtual void handleEvent(const unsigned int &event, const unsigned int &channel) = 0;
    };

} // engine

#endif //GAME_ENGINE_IOBSERVER_H
