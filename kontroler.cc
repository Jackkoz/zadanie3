#include <string>
#include "kontroler.h"
#include "sejf.h"

using namespace std;

//Constants used for output concerning safe condition.

const static string safeCondition[] = {"ALARM: WLAMANIE\n", "ALARM: ZMANIPULOWANY\n", "OK\n"};
const static int breakIn = 0;
const static int manipulation = 1;
const static int ok = 2;

Kontroler::Kontroler(const Sejf& Safe) : controlledSafe(Safe) {}

Kontroler::operator bool() const {
    return (controlledSafe.access_count > 0);
}

bool Kontroler::brokenSafe() const {
    return controlledSafe.broken;
}

bool Kontroler::manipulatedSafe() const {
    return controlledSafe.manipulated;
}

std::ostream& operator<<(std::ostream &out, Kontroler const &k) {
    std::string safeMessage;

    if (k.brokenSafe())
        safeMessage = safeCondition[breakIn];
    else if (k.manipulatedSafe())
        safeMessage = safeCondition[manipulation];
    else
        safeMessage = safeCondition[ok];

    return out << safeMessage;
}
