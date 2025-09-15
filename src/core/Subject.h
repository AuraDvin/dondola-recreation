#ifndef DONDOLAGAME_RECREATION_SUBJECT_H
#define DONDOLAGAME_RECREATION_SUBJECT_H
#include <vector>
#include <string>

class Observer;

class Subject {
public:
    Subject() = default;

    void assignObserver(Observer &observer);

    void removeObserver(Observer &observer);

    void send() const;

    void send(const std::string &message) const;

private:
    std::vector<Observer *> observers;
};

#endif //DONDOLAGAME_RECREATION_SUBJECT_H
