//
// Created by aura on 12. 09. 25.
//

#ifndef DONDOLAGAME_RECREATION_OBSERVER_H
#define DONDOLAGAME_RECREATION_OBSERVER_H
#include <stdexcept>
#include <string>


class Subject;

/// This will recieve the event from object, there can also be a string argument passed
/// for example if you want to move and send the direction, you can do that, but if you just
/// want to toggle what direction the player is facing you can also just toggle scale for example
/// By default they throw logic error to require you overload them properly.
class Observer {
public:
    explicit Observer(Subject *subject);

    Observer() = default;

    virtual ~Observer() = default;

    /// Handlers for the Subject they're listening to
    virtual void onNotify() = 0;
    virtual void onNotify(const std::string &message) {
        throw std::logic_error("Not implemented");
    }
};


#endif //DONDOLAGAME_RECREATION_OBSERVER_H
