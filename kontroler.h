#ifndef KONTROLER_H
#define KONTROLER_H

#include <ostream>

class Sejf;

class Kontroler {

    public:
        //List of friendly classes and functions.
        friend class Sejf;
        friend std::ostream& operator<<(std::ostream &out, const Kontroler& k);

        //Operator returns true if the Kontroler's
        //Sejf has more than 0 remaining access counts.
        operator bool() const;

        //List of forbidden comparison operators.
        bool operator<(const Kontroler& k1) = delete;
        bool operator>(const Kontroler& k1) = delete;
        bool operator<=(const Kontroler& k1) = delete;
        bool operator>=(const Kontroler& k1) = delete;
        bool operator==(const Kontroler& k1) = delete;

    private:
        //The Sejf controlled by this Kontroler.
        const Sejf& controlledSafe;

        //The private Kontroler constructor that
        //can be called only from within a Sejf object.
        Kontroler(const Sejf& Safe);

        //Returns true if Kontroler's Sejf was accessed
        //and its access count was less than 1.
        bool brokenSafe() const;

        //Returns true if Kontroler's Sejf access count
        //number was modifed by the *=, +=, or -= operators.
        bool manipulatedSafe() const;
};

//Operator returns the message about Kontroler's Sejf
//confition to the out stream.
std::ostream& operator<<(std::ostream &out, const Kontroler& k);

#endif