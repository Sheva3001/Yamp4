#include <iostream>
#include <fstream>
using namespace std;

struct Dice {
	int left, right;
};

void createDice(Dice*& array, int N) {
	if (N > 28)
		cout << "Превышено количество костей!" << endl;
	else {
		int counter = 0;
		for (int i = 0; i <= 6; i++) {
			for (int j = i; j <= 6; j++) {
				if (counter < N) {
					array[counter].left = i;
					array[counter].right = j;
					counter++;
				}
			}
		}
	}
}

void createDiceFromFile(ifstream& file, Dice*& array, int& N) {
	file >> N;
	if (N > 28)
		cout << "Превышено количество костей!" << endl;
	else {
		array = new Dice[N];
		for (int i = 0; i < N; i++) {
			file >> array[i].left;
			file >> array[i].right;
		}
	}
}

void backtracking(Dice* array, Dice*& temp,Dice*& newArray, bool* b, int N, int cur, int& max) {
	for (int i = 0; i < N; i++) {
		if ((temp[cur - 1].right == array[i].left || cur == 0) && b[i]) {
			temp[cur] = array[i];
			b[i] = false;
			backtracking(array, temp, newArray, b, N, cur + 1, max);
			b[i] = true;
		}
		if ((temp[cur - 1].right == array[i].right || cur == 0) && b[i]) {
			swap(array[i].left, array[i].right);
			temp[cur] = array[i];
			b[i] = false;
			backtracking(array, temp, newArray, b, N, cur + 1, max);
			b[i] = true;
		}
	}
	for (int i = 0; i < N; i++)
		cout << "[" << temp[i].left << "|" << temp[i].right <<"]";
	cout << endl;
	//if (cur > max) {
	//	max = cur;
	//	for (int i = 0; i < N; i++)
	//		newArray[i] = temp[i];
	//}
}

void Backtracking(Dice* array, int N) {
	Dice* temp = new Dice[N]; Dice* newArray = new Dice[N];
	bool* b = new bool[N]; int cur, max; cur = max = 0;
	for (int i = 0; i < N; i++)
		b[i] = true;
	backtracking(array, temp, newArray, b, N, cur, max);
	for (int i = 0; i < max; i++)
		cout << "[" << newArray[i].left << "|" << newArray[i].right << "] ";
}

int main() {
	setlocale(LC_ALL, "Russian");
/*
	int N =20;
	Dice* array = new Dice[N];
	createDice(array, N);
*/
	Dice* array; int N = 0;
	ifstream file("file.txt");
	if (!file.is_open())
		cout << "Ошибка открытия файла" << endl;

	createDiceFromFile(file, array, N);
	Backtracking(array, N);

	return 0;
}