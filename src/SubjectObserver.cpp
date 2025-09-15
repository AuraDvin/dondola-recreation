#include "Subject.h"
#include "Observer.h"
#include <algorithm>

Observer::Observer(Subject &subject) {
    subject.assignObserver(*this);
}

void Subject::assignObserver(Observer &observer) {
    observers.push_back(&observer);
}

void Subject::removeObserver(Observer &observer) {
    const auto it = std::remove(observers.begin(), observers.end(), &observer);
    observers.erase(it);
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