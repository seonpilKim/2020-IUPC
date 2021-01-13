#include <iostream>

using namespace std;

string Find__Ideal_Type(string);

int main() {
	string MBTI;

	cin >> MBTI;

	cout << Find__Ideal_Type(MBTI);

	return 0;
}

string Find__Ideal_Type(string MBTI) {
	char idealtype[5];

	if (MBTI.at(0) == 'I') idealtype[0] = 'E';
	else idealtype[0] = 'I';
	if (MBTI.at(1) == 'S') idealtype[1] = 'N';
	else idealtype[1] = 'S';
	if (MBTI.at(2) == 'F') idealtype[2] = 'T';
	else idealtype[2] = 'F';
	if (MBTI.at(3) == 'J') idealtype[3] = 'P';
	else idealtype[3] = 'J';
	idealtype[4] = NULL;

	return idealtype;
}