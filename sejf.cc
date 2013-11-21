#include <string>
#include <iostream>
#include <utility>
#include <climits>
#include <stdexcept>
#include "kontroler.h"
#include "sejf.h"

using namespace std;

Sejf::Sejf(string s, int i = 42)
    : text(s)
    , access_count(i)
    , broken(false)
    , manipulated(false)
{
    if (i < 0)
        throw invalid_argument("Access number < 0. Failure.");
}

Kontroler Sejf::kontroler() {
    Kontroler kontrolerForSafe(*this);
    return kontrolerForSafe;
}

Sejf::Sejf(Sejf&& s) 
    : text(std::move(s.text))
    , access_count(std::move(s.access_count))
{}

Sejf& Sejf::operator= (Sejf&& s) {
    if (this != &s) {
        text = std::move(s.text);
        access_count = std::move(s.access_count);
    }

    return *this;
}

void Sejf::operator+= (int i) {
    int new_count = access_count + i;
    if (new_count >= access_count) {
        access_count = new_count;
        manipulated = true;
    }
}

void Sejf::operator-= (int i) {
    int new_count = access_count - i;
    if (new_count <= access_count && new_count >= 0) {
        access_count = new_count;
        manipulated = true;
    }
}

void Sejf::operator*= (int i) {
    int new_count = access_count * i;
    if (new_count >= access_count) {
        access_count = new_count;
        manipulated = true;
    }
}

int16_t Sejf::operator[] (int i) {
    if (access_count < 1 && text.size() > i) {
        broken = true;
        return -1;
    }

    if (access_count > 0 && text.size() > i) {
        access_count--;
        return text[i];
    } else
        return -1;
}