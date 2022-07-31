#include <iostream>
using namespace std;

class MatrixHolder
{
	public:
		virtual void getMatrix()
		{
			cout << "MatrixHolder" << endl;
		}
};

class View : public MatrixHolder
{
	public:
		virtual void getMatrix()
		{
			cout << "View" << endl;
		}
};

class Projection : public MatrixHolder
{
	public:
		virtual void getMatrix()
		{
			cout << "Projection" << endl;
		}
};

class Camera : public View, public Projection
{
	public:
		virtual void getMatrix()
		{
			cout << "Camera" << endl;
		}
};

class Camera2 : public View, public Projection
{

};

int main()
{
	Camera c;
	View(c).getMatrix();
	Projection(c).getMatrix();
	c.getMatrix();
	
	cout << endl;

	Camera2 c2;
	View(c2).getMatrix();
	Projection(c2).getMatrix();
	c2.getMatrix();//error:request for member 'getMatrix' is ambiguous
	
	system("pause");
	return 0;
}
