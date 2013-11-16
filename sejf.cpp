#include <string>
#include <iostream>
#include <utility>
#include <climits>

using namespace std;

class Sejf {

	public :
		Sejf(string, int);
		void operator += (int);
		void operator -= (int);
		void operator *= (int);
		int16_t operator [] (int);

		Sejf(const Sejf&) = delete;
		//DEBUG
		string getText() {return text;}
		int getAccess() {return access_count;}
		//END DEBUG

	private:
		string text;
		int access_count;
};

Sejf::Sejf(string s, int i = 42) {
	text = s;
	access_count = i;
}

void Sejf::operator+= (int i) {
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

	//std::swap(s1,s2); //do zrobienia, bo też nie działa

	//Sejf s3(s1); //NIE DZIAŁA
	//Sejf s3 = s1; //NIE DZIAŁA
	//END DEBUG

	return 0;
}