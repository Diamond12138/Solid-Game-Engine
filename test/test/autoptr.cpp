#include <iostream>
#include <memory>
#include <vector>
using namespace std;

int main()
{
	//shared_ptr<float[]> array = make_shared<float[],default_delete<float[]>()>(new float[]{6,6,6});
	/*unique_ptr<float[]> array(new float[10]{6,6,6});
	cout << sizeof(array.get()) << endl;*/
	vector<float> array{6,6,6};
	cout << array.size() * sizeof(float) << endl;
	system("pause");
	return 0;
}
