#ifndef SEJF_H
#define SEJF_H

#include <string>

class Kontroler;

class Sejf {

    public :
        friend class Kontroler;

        /**
        * Basic constructor. The default int value should it not be
        * provided is 42.
        */
        Sejf(std::string, int);

        /**
        * Operator += increases access count of Sejf by given integer,
        * as long as the operation does not result in a decrease of the
        * access count and does not set it to a negative integer,
        * otherwise does nothing.
        */
        void operator += (int);

        /**
        * Operator -= decreases access count of Sejf by given integer,
        * as long as the operation does not result in an increase of the
        * access count and does not set it to a negative integer,
        * otherwise does nothing.
        */
        void operator -= (int);

        /**
        * Operator *= multiplies the access count of Sejf by given integer,
        * as long as the operation does not result in a decrease of the
        * access count and does not set it to a negative integer,
        * otherwise does nothing.
        */
        void operator *= (int);

        /**
        * The [] operator is used to access Sejf's content at index given
        * the input integer. If index is invalid or access count
        * is less than 1, returns -1.
        */
        int16_t operator [] (int);

        /**
        * The method returning Sejf's Kontroler object.
        */
        Kontroler kontroler();

        // Deleted copying constructors and operators.
        Sejf(const Sejf&) = delete;
        Sejf& operator=(const Sejf&) = delete;

        // Rvalue copying constructors and operators.
        Sejf(Sejf&&);
        Sejf& operator=(Sejf&&);

        //DEBUG
        std::string getText() {return text;}
        int getAccess() {return access_count;}
        //END DEBUG

    private:
        /**
        * Manipulated is true if the Sejf's access count was changed
        * using the +=, -=, and *= operators.
        */
        bool manipulated;

        /**
        * Broken is true if the Sejf was accessed while having
        * access count == 0.
        */
        bool broken;

        /**
        * The text value stored in Sejf.
        */
        std::string text;

        /**
        * The count of currently remaining accesses of Sejf.
        */
        int access_count;
};

#endif