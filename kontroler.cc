#include <string>
#include "kontroler.h"
#include "sejf.h"

using namespace std;

//Constants used for output concerning safe condition.

const 
        string safeCondition[] = {"ALARM: WLAMANIE\n", "ALARM: ZMANIPULOWANY\n", "OK\n"};
        int breakIn = 0;
        int manipulation = 1;
        int ok = 2;

Kontroler::Kontroler(const Sejf& Safe) : controlledSafe(Safe) {}

Kontroler::operator bool() const {
        if (controlledSafe.access_count > 0)
                return true;
        else
                return false;
}

bool Kontroler::brokenSafe() const {
        if (controlledSafe.broken)
                return true;
        else
                return false;
}

bool Kontroler::manipulatedSafe() const {
        if (controlledSafe.manipulated)
                return true;
        else
                return false;
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