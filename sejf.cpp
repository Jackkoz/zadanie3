#include <string>
#include <iostream>
#include <utility>
#include <climits>
#include <stdexcept>

using namespace std;

class Sejf {

	public :
		Sejf(string, int);
		//~Sejf() {delete &text;};
		void operator += (int);
		void operator -= (int);
		void operator *= (int);
		int16_t operator [] (int);

		Sejf(const Sejf&) = delete;
		Sejf& operator=(const Sejf&) = delete;
		Sejf(Sejf&&);
   		Sejf& operator=(Sejf&&);
		//DEBUG
		string getText() {return text;}
		int getAccess() {return access_count;}
		//END DEBUG

	private:
		string text;
		int access_count;
};

Sejf::Sejf(string s, int i = 42) {
	if (i < 0)
		throw invalid_argument("Access < 0. Failure.");
	text = s;
	access_count = i;
}

Sejf::Sejf(Sejf&& s) 
	: text("")
   , access_count(0)
{
	text = s.text;
	access_count = s.access_count;

	s.text = "";
	s.access_count = 0;
}

Sejf& Sejf::operator= (Sejf&& s) {

	if (this != &s) {

		text = s.text;
		access_count = s.access_count;

		s.text = "";
		s.access_count = 0;
	}
	return *this;
}

void Sejf::operator+= (int i) {;
	int new_count = access_count + i;
	if (new_count > access_count)
		access_count = new_count;
}

void Sejf::operator-= (int i) {
	int new_count = access_count - i;
	if (new_count < access_count && new_count >= 0)
		access_count = new_count;
}

void Sejf::operator*= (int i) {
	int new_count = access_count * i;
	if (new_count > access_count)
		access_count = new_count;
}

int16_t Sejf::operator[] (int i) {
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
	cout << "MOVING\n";
	Sejf s3 = std::move(s1); 
	cout << "s1: " << s1.getText() << " " << s1.getAccess() << endl;
	cout << "s3: " << s3.getText() << " " << s3.getAccess() << endl;
	s1[1];
	s3[1];
	cout << "s1: " << s1.getText() << " " << s1.getAccess() << endl;
	cout << "s3: " << s3.getText() << " " << s3.getAccess() << endl;
	cout << "*** END TEST ***\n\n";

	//obecnie powyższe przenosi sejf i zeruje ten, z które wzięło

	std::swap(s3, s3);
	s3 = std::move(std::move(s3));
	cout << "s3: " << s3.getText() << " " << s3.getAccess() << endl;

	//Sejf s3(s1); //Sypie kompilację
	//Sejf s3 = s1; //Sypie kompilację
	//END DEBUG

	return 0;
}