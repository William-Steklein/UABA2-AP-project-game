#ifndef GAME_ENGINE_ISUBJECT_H
#define GAME_ENGINE_ISUBJECT_H


#include <memory>
#include <set>

#include "engine/observer-pattern/IObserver.h"

namespace engine {

    class ISubject {
    private:
        std::set<std::shared_ptr<IObserver>> _observers;

    public:
        void addObserver(const std::shared_ptr<IObserver> &observer);

        void removeObserver(const std::shared_ptr<IObserver> &observer);

        virtual void notifyObservers();

        virtual void notifyObservers(const unsigned int &event, const unsigned int &channel);
    };

} // engine

#endif //GAME_ENGINE_ISUBJECT_H
