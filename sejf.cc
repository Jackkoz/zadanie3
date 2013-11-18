#include <string>
#include <iostream>
#include <utility>
#include <climits>
#include <stdexcept>
#include "kontroler.h"
#include "sejf.h"

using namespace std;

Sejf::Sejf(string s, int i = 42) { //lista inicjująca
    if (i < 0)
        throw invalid_argument("Access number < 0. Failure.");

    text = s;
    access_count = i;
    broken = false;
    manipulated = false;
}

Kontroler Sejf::kontroler() {
    Kontroler kontrolerForSafe(*this);
    return kontrolerForSafe;
}

Sejf::Sejf(Sejf&& s)
    // : text("")
    // , access_count(0)
{
    //W całości jednym szablonem, np swap albo move
    text = std::move(s.text); //magiczne move
    access_count = s.access_count;

    //s.text = "";
    s.access_count = 0;
}

Sejf& Sejf::operator= (Sejf&& s) { //jak wyżej
    if (this != &s) {
        text = s.text;
        access_count = s.access_count;

        s.text = "";
        s.access_count = 0;
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

int main() {

    //DEBUG
    Sejf s1("aaa", 5);
    cout << s1.getText() << endl;
    cout << s1.getAccess() << endl;
    cout << s1[1] << endl;
    cout << s1[5] << endl;
    cout << s1.getAccess() << endl;
    Sejf s2("abc");
    cout << s2.getText() << endl;
    cout << s2.getAccess() << endl;
    s2 += 5;
    cout << s2.getAccess() << endl;
    s2 -= 1000;
    cout << s2.getAccess() << endl;
    s2 -= 45;
    cout << s2.getAccess() << endl;
    s2 *= INT_MAX;
    cout << s2.getAccess() << endl;
    cout << INT_MAX << endl;

    //Sejf s3("asdf", -1); // działa jak chcemy, czyli rzuca wyjątek

    cout << "*** SWAP TEST ***\n";
    cout << "s1: " << s1.getText() << " " << s1.getAccess() << endl;
    cout << "s2: " << s2.getText() << " " << s2.getAccess() << endl;
    std::swap(s1,s2);
    cout << "SWAPPING\n";
    cout << "s1: " << s1.getText() << " " << s1.getAccess() << endl;
    cout << "s2: " << s2.getText() << " " << s2.getAccess() << endl;
    cout << "*** END TEST ***\n\n";

    cout << "*** MOVE TEST ***\n";
    cout << "s1: " << s1.getText() << " " << s1.getAccess() << endl;
    cout << "MOVING\n";#endif
    Kontroler kon1 = s1.kontroler();
    Sejf s3 = std::move(s1);
    cout << kon1;
    cout << "s1: " << s1.getText() << " " << s1.getAccess() << endl;
    cout << "s3: " << s3.getText() << " " << s3.getAccess() << endl;
    s1[1];
    s3[1];
    cout << "s1: " << s1.getText() << " " << s1.getAccess() << endl;
    cout << "s3: " << s3.getText() << " " << s3.getAccess() << endl;
    cout << "*** END TEST ***\n\n";

    cout << "*** KONTROLER TEST ***\n";
    Sejf a1("aaa", 2);
    Kontroler k1 = a1.kontroler();
    cout << k1;
    if (k1) {
            cout << "WYGLADA NA TO ZE MOZNA WBIJAC DO SEJFU\n";
    }
    Sejf a2("bbb", 2);
    Kontroler k2 = a2.kontroler();
    /*
    if (k1 < k2) {
            cout << "NO PANIE CZEMU TO SIE KOMPILUJE!?\n";
    }
    if (k1 <= k2) {
            cout << "NO PANIE TOZ TO SIE MA NIE KOMPILOWAC\n";
    }
    if (k1 == k2) {
            cout << "A COZ TO ZA KOMPILOWANIE?\n";
    }
    Powyzsze proby porownania kontrolerow koncza sie bledem kompilacji
    zgodnie z przykladem do zadania.
    */
    a1 *= 1;
    cout << k1;
    a1[2];
    a1[2];
    a1[2];
    cout << k1;
    cout << "*** END KONTROLER TEST ***\n";
    //obecnie powyższe przenosi sejf i zeruje ten, z które wzięło

    std::swap(s3, s3);
    s3 = std::move(std::move(s3));
    cout << "s3: " << s3.getText() << " " << s3.getAccess() << endl;

    //Sejf s3(s1); //Sypie kompilację
    //Sejf s3 = s1; //Sypie kompilację
    //END DEBUG

    return 0;
}