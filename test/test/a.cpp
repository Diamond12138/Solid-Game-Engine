#include <iostream>
#include "a.hpp"
using namespace std;

int main()
{
	A::c.n = 999;
	cout << A::c.n << endl;
	system("pause");
	return 0;
}
