#include <iostream> 
#include <cstdlib>
#include <ctime>
using namespace std;


int allpk();
void color(int color);
void num(int num);
char check(char ans);
void one_time(int deal[52], int allpk[52][3]);


int main() 
{	int poker[52][3] = {0}, deal[52] = {0}, i, index, temp;
	char ans = 'y';
	
	//Define pokers.
	for (i = 0; i <= 12; ++i) {poker[i][0] = 1; poker[i][1] = i + 1;}
	for (i = 13; i <= 25; ++i) {poker[i][0] = 2; poker[i][1] = i - 12;}
	for (i = 26; i <= 38; ++i) {poker[i][0] = 3; poker[i][1] = i - 25;}
	for (i = 39; i <= 51; ++i) {poker[i][0] = 4; poker[i][1] = i - 38;}
	
	for (i = 0; i <= 51; ++i) {
		if (poker[i][1] <= 10) poker[i][2] = poker[i][1] * 2; //For the convenience, I double the value of each poker.
		else poker[i][2] = 1;
	}
	
	while (ans == 'y') {
		
		//Shuffle the pokers.
		srand(time(NULL));
		
		for (i = 0; i <= 51; ++i) deal[i] = i + 1;
		for (i = 51; i > 0; i--) {
			index = rand() % i;
			temp = deal[i];
			deal[i] = deal[index];
			deal[index] = temp;
		}

		one_time(deal, poker);
		
		cout << "\nPlay again? (y/n): ";
		cin >> ans;
		check(ans);
		cout << "\n\n";
	}
	return 0;
}



//Show the color of the poker.
void color(int index)
{
	switch (index) {
		case 1: cout << "Heart"; break;
		case 2: cout << "Spade"; break;
		case 3: cout << "Diamond"; break;
		case 4: cout << "Club"; break;
	}
}



//Show the number of the poker.
void num(int index) 
{
	switch (index) {
		case 1: cout << "A  "; break;
		case 2: cout << "2  "; break;
		case 3: cout << "3  "; break;
		case 4: cout << "4  "; break;
		case 5: cout << "5  "; break;
		case 6: cout << "6  "; break;
		case 7: cout << "7  "; break;
		case 8: cout << "8  "; break;
		case 9: cout << "9  "; break;
		case 10: cout << "10  "; break;
		case 11: cout << "J  "; break;
		case 12: cout << "Q  "; break;
		case 13: cout << "K  "; break;
	}
}



char check(char ans)
{	
	while ((ans != 'y') && (ans != 'n')) {
		cout << "\nPlease input 'y' or 'n': ";
		cin >> ans;
	}
	return (ans);
}



//One time of the game.
void one_time(int deal[52], int pk[52][3])
{	int k, i = 1, j = 1, p_sum = 0, c_sum = 0; //Player's and computer's sums of pokers.
	char ans; //Player's answer.
	
	//Player's turn.
	cout << "Player's Turn\n";
	
	p_sum += (pk[deal[0]][2] + pk[deal[1]][2]);
	
	cout << "Player gets the pokers: ";
	color(pk[deal[0]][0]); num(pk[deal[0]][1]);
	color(pk[deal[1]][0]); num(pk[deal[1]][1]);
	
	cout << "\n\nTake another poker? (y/n): ";
	cin >> ans;
	check(ans);
	
	while (ans == 'y') {
			++i;
			p_sum += pk[deal[i]][2];
			
			cout << "\n\nPlayer takes another poker: ";
			for (k = 0; k <= i; ++k) 
				{color(pk[deal[k]][0]); num(pk[deal[k]][1]);}
			
			if (p_sum > 42) {
				cout << "\nSorry, you lose." << endl; break;
			}
			cout << "\n\nTake another poker? (y/n): ";
			cin >> ans;
			check(ans);
	}
	
	//Computer's turn.
	if (ans == 'n') {
		cout << "\n\nComputer's Turn\n";
		
		c_sum += (pk[deal[i + 1]][2] + pk[deal[i + 2]][2]);
		
		cout << "Computer gets the pokers: ";
		color(pk[deal[i + 1]][0]); num(pk[deal[i + 1]][1]);
		color(pk[deal[i + 2]][0]); num(pk[deal[i + 2]][1]);
		
		while (c_sum < p_sum) {
			++j;
			c_sum += pk[deal[i + j + 1]][2];
			
			cout << "\n\nComputer gets another pokers: ";
			for (k = i + 1; k <= i + j + 1; ++k) 
				{color(pk[deal[k]][0]); num(pk[deal[k]][1]);}
		}
		if (c_sum > p_sum) {
			if (c_sum > 42) cout << "\nCongratulations! You win!" << endl;
			else cout << "\nSorry, you lose." << endl;
		}
		else if (c_sum = p_sum) {
				if (i < j) cout << "\nSorry, you lose." << endl;
				if (i >= j) {
					if (c_sum + pk[deal[i + j + 2]][2] <= 42) {
						for (k = i + 1; k <= i + j + 2; ++k) 
							{color(pk[deal[k]][0]); num(pk[deal[k]][1]);}
						cout << "\nSorry, you lose." <<endl;
					}
					else {
						if (i = j) cout << "\nTie." << endl;
						if (i > j) cout << "\nCongratulations! You win!" << endl;
					}
				}
			} 
	}
}
