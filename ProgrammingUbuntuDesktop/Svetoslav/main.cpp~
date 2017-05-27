#include <iostream>
	using namespace std;

void min_and_max_num() {
	int counterOfNum, num, i;
	int maxNum, minNum;
	cout << "Enter the counter of numbers: ";
	cin >> counterOfNum;
	if (counterOfNum != 0) {
		for (i = 1; i <= counterOfNum; i++) {
			cout << "number " << i << " = ";
			cin >> num;
			if(i==1){
				maxNum = minNum = num;
			}
			if(maxNum < num){
				maxNum = num;
			}
			if(minNum > num){
				minNum = num;
			}
			
		}
		cout << "The maximum number is: ";
		cout << maxNum << endl;
		cout << "The minimum number is: " << minNum << endl;
	} else {
		cout << "No have numbers.";
	}

}

int main() {
	min_and_max_num();
	return 0;
}
