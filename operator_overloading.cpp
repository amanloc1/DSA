#include <bits/stdc++.h>
using namespace std;

class Complex{
	public:
	int r,i;
	//() - takes multuple arguments
	//+ - takes zero or one arguments
	void operator () (Complex C, Complex D){
		r = r + C.r + D.r;
		i = i + C.i + D.i;
	}

};

int main(int argc, char const *argv[])
{
	Complex C = {1,2};
	Complex D = {2,5};
	Complex E = {4,7};
	C(D,E);

	cout<<C.r<<" "<<C.i<<endl;	



	


    return 0;
}