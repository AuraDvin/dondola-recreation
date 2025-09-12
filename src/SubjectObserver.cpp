#include "Subject.h"
#include "Observer.h"

Observer::Observer(Subject *subject) {
    subject->assignObserver(*this);
}

void Subject::assignObserver(Observer &observer) {
    observers.push_back(&observer);
}

void Subject::send(const std::string &message) {
    for (Observer *observer : observers) {
        observer->onNotify(message);
    }
}

void Subject::send() {
    for (Observer *observer : observers) {
        observer->onNotify();
    }
}