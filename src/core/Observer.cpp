#include "Observer.h"
#include "Subject.h"

Observer::Observer(Subject &subject) {
    subject.assignObserver(*this);
}