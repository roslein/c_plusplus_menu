#include <iostream>
using namespace std;

int main() {
	int x1,x2,x3;
	

	cout << "Select a menu" << endl;
	cout << "1.food 2. drink" << endl;
	cin >> x1;
	switch (x1) {
	case 1:
		cout << "You have selected food. Which food?"<<endl;
		cout << "1. Korean 2. American 3.Chinese" << endl;
		cin >> x2;
		if (x2 == 1) {
			cout << "You have selected an Korean food. Which Korean food?"<<endl;
			cout << "1.Rice 2. Bulgogi"<<endl;
			cin >> x3;
			if (x3 == 1) {
				cout << "Enjoy your Rice!";
			}
			else if (x3 == 2) {
				cout << "Enjoy your Bulgogi!";
			}
			else {
				cout << "there is no such menu";
			}
		}
		else if (x2 == 2) {
			cout << "You have selected an American food. Which American food?"<<endl;
			cout << "1.Hamburger 2. Salad"<<endl;
			cin >> x3;
			if (x3 == 1) {
				cout << "Enjoy your Hamburger!";
			}
			else if (x3 == 2) {
				cout << "Enjoy your Salad!";
			}
			else {
				cout << "there is no such menu";
			}
		
		}
		else if (x2 == 3) {
			cout << "You have selected an Chinese food. Which Chinese food?"<<endl;
			cout << "1.Noodle 2. Dimsum" <<endl;
			cin >> x3;
			if (x3 == 1) {
				cout << "Enjoy your Noodle!";
			}
			else if (x3 == 2) {
				cout << "Enjoy your Dimsum!";
			}
			else {
				cout << "there is no such menu";
			}
		}
		else {
			cout << "there is no such menu";
		}
		break;
	case 2:
		cout << "You have selected drink. Which drink?";
		cout << "1. Cola 2. Orange juice 3. Water" << endl;
		cin >> x2;
		if (x2 == 1) {
			cout << "Enjoy your Cola!";
		}
		else if (x2 == 2) {
			cout << "Enjoy your Orange juice!";
		}
		else if (x2 == 3) {
			"Enjoy your Water!";
		}
		else {
			cout << "there is no such menu";
		}
		break;

	default:
		cout << "there is no such menu";


	}




	return 0;
}