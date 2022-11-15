#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<stack>
using namespace std;


vector < int   >character[26];    //int array of vectors these will be containing the index of certain character in the string


vector < int   >complementcharacter[26];

bool check(bool vecbool[], int count)
{
	static int	trn = 0;
	//cout << "trn " << trn << endl;

	for (int i = 0; i < 26; i++) {
		bool		atpresent = false;
		int		switchh = 0;
		for (int j = 0; j < character[i].size(); j++) {
			if (switchh == 0) {
				atpresent = vecbool[character[i][j]];
				switchh = 1;
				continue;
			}
			if (atpresent != vecbool[character[i][j]]) {
				trn++;
				//cout << "x1\n";
				return false;
			}
		}
		// checking if a variable in the expression have same value at every index


		switchh = 0;


		for (int j = 0; j < complementcharacter[i].size(); j++) {
			if (switchh == 0) {
				atpresent = vecbool[complementcharacter[i][j]];
				switchh = 1;
				continue;
			}
			if (atpresent != vecbool[complementcharacter[i][j]]) {
				trn++;
				//cout << "x2\n";
				return false;
			}
		}
		// checking for complement cahracter if all the values are same at every index in the expressin for the same variable


		if (character[i].size() != 0 && complementcharacter[i].size() != 0) {
			//cout << "yoyo\n";
			if (vecbool[character[i][0]] == vecbool[complementcharacter[i][0]]) {     //validating complement relation
				trn++;
				//cout << "x3\n";
				return false;
			}
		}
	}
	trn++;
	//cout << "x4\n";
	return true;
}
//check fuction is completed





/***************************************************************************************************************/
bool func(string g)
{
	/***************************************************************************************************************/
	stack < char > var;
	char		exp = '-';
	for (int i = 0; i < g.size(); i++) {
		if (g[i] == '(') {
			var.push(g[i]);
		}
		if (g[i] == ')') {
			char		f = var.top();
			//cout << f << "16" << endl;
			var.pop();
			var.pop();
			var.push(f);
		}
		if (g[i] == '&' || g[i] == '|') {
			exp = g[i];
		}
		if (g[i] == '1' || g[i] == '0') {

			if (exp == '-') {
				//cout << g[i] << "Y" << endl;
				var.push(g[i]);
			}
			if (exp != '-') {
				bool		t = 0;
				if (exp == '&') {

					bool	now = var.top() - 48;
					//cout << i << " i " << now << endl;
					t = now & (g[i] - 48);
					now = t;
					//cout << "t" << now << endl;
					var.pop();
					if (now == 0) {
						var.push('0');
					} else {
						var.push('1');
					}
					exp = '-';
				} else {
					bool		now = var.top() - 48;
					//cout << i << " i " << now << endl;

					t = now | (g[i] - 48);
					//cout << "yes " << t << endl;
					now = t;
					//cout << now << endl;
					var.pop();
					if (now == 0) {
						var.push('0');
					} else {
						var.push('1');
						//cout << "u" << endl;
					}

					exp = '-';
				} //algo error may be present here

			}
		}
	} //forloop ended

		if (var.top() == '1') {
		return true;
	} else {
		return false;
	}

}				/********************************************************************************************************/

bool		globalt = false;


void print(bool vecbool[], int count)
{	
	static bool	t = false;
	bool		k = check(vecbool, count);
	if (k == false) {

		return;
	}
	if(t == false){
		t = true;
		return;
	}
	if (t == true) {
		cout << "satisfiable\n";
		globalt = true;
		t = true;
	}
	for (int i = 0; i < count; i++) {
		cout << vecbool[i] << " ";
	}


	cout << endl;
}

/***********************************************************************************/

void backtrack(vector < int >vec, string g, int index, bool vecbool[], int count)
{
	//pahle wah usse 0 rahkega then backtrack then if index == vec.size()
		if (index == vec.size() - 1) {
			//now apply your function

			g[vec[index]] = '0';
			vecbool[index] = false;
			bool		f = func(g);
			//Assume for now
			//	func(g);
			if (f == true) {
				print(vecbool, count);
			}
			g[vec[index]] = '1';
			vecbool[index] = true;
			f = func(g);
			if (f == true) {
				print(vecbool, count);
			}
            
			return;
		} // base case completed
	/******************
    
    
    
    gap for understanding base case vs non base case
    
    
    
    
    //starting non- base case
         *****************/

	g[vec[index]] = '0';

	vecbool[index] = false;

	backtrack(vec, g, index + 1, vecbool, count);

	g[vec[index]] = '1';
	vecbool[index] = true;
	backtrack(vec, g, index + 1, vecbool, count);



}











/***********************************************/
bool IsLoggedIn()
{
	string username, password, un, pw;
	
	cout << "Enter Username : "; cin >> username;
	cout << "Enter Password : "; cin >> password;
	
	ifstream read("data\\" + username + ".txt");
	getline(read, un);
	getline(read, pw);

	if (un == username && pw == password)
	{
		return true;
		
	}
	else 
	{
		return false;
	}
}
   
    int main()
    {
    	


    	int choice;
    	cout << "1: Register\n2: Login\nYourChoice:  "; cin >> choice;
		if (choice == 1)
		{
			string username, password;
			
			cout << "select a username: "; cin >> username;
			cout<< "select a password: "; cin >> password;
			
			ofstream file;
			file.open("data\\" + username + ".txt");
			file << username << endl << password;
			file.close();
			
			main();
			
		}
		else if (choice == 2)
		{
			bool status = IsLoggedIn();
			
			if (!status) 
			{
				cout << "False login!" << endl;
				system("PAUSE");
				return 0;
				
			}
		else 
		{
			cout << "Login Successful! " << endl;
			cout<<"Enter the input in this format (a|b)&(c|x)  etc...\n";
			string g;
    	cin>>g;
	//cout<<"you have entered the g\n";
	int		count = 0;
	vector < int   >vec;


			for (int i = 0; i < g.size(); i++) {
		if (g[i] != '(' && g[i] != ')' && g[i] != '&' && g[i] != '|') {

			if ('a' <= g[i] && g[i] <= 'z') {
				int		h = g[i] - 97;
				character[h].push_back(count);
			}
			if ('A' <= g[i] && g[i] <= 'Z') {
				int		h = g[i] - 'A';
				complementcharacter[h].push_back(count);
			}
			count++;   // count represents index


			vec.push_back(i);
		}
	}


	bool		vecbool   [count];
	backtrack(vec, g, 0, vecbool, count);
	if (globalt == false) {
		cout << "unsatisfiable\n";
	}

				



				return 1;
			
			}	
		}
    	
	}
	
	
	
	
	
	
