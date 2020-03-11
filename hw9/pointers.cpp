#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;
float f{ 3.5f };

// declarations.
struct A {
	int x_ = 0;
	int y_ = 0;

	virtual int fnvretint() { return 11; }
	int fnpi( int* ) { return 12; }
	int fnvoidparams() { return 13; }
	double fntakingfn( double (*pf)(float &) ) { return pf(f); }
};
struct B : public A {
  int z_ = 0;
};
int myIntReturnFunction() { return 1; }
void myVoidFnTakingVoidFn( void (*)() ) {}
void myVoidFn() {}
char* myPszFn( char*, char* ) { static char szBuf[10] = "hello"; return szBuf; }

double myDoubleReturningFunction(float&) { return 15.5; }
A a;

int main()
{
	//
	// first set
	//

	// int*
	int i = 2;
	int* pi = &i;
	cout << *pi << endl;

	// int&
	int& i2 = i;
    i = 5;
	cout << i2 << endl;

	// double
	double d = 1.414;
	cout << d << endl;

	// A * (A is any appropriate class).
    B b;
    b.x_ = 2;
	b.y_ = 3;
	A* pa = &b;
    A &ar{b};
	cout << pa << endl;

	// char const *
    char const * psz = "hello";
    char const *psz2 = "world"; 
	cout << psz << endl;

	// const char&
	char const ch = 'x';
    char const & chr = ch;
    char & chrnc = const_cast<char &>(ch);
    cout << chr << endl;

	// long[7]
	long pi7[] = { 1, 2, 3, 4, 5, 6, 7 };
	cout << pi7 << endl;
	long *ppi7 = pi7;

	// int**
	int** ppi = &pi;
    cout << ppi << endl;
    cout << **ppi << endl;

	// int*&
	int*& pi2 = pi;
	cout << pi2 << endl;

	// float&
	float flt = 3.14159265f;
	float& flt2 = flt;
	cout << flt2 << endl;

	// int (*)()
	// (See http://www.newty.de/fpt/index.html)
	int (*pf)() = myIntReturnFunction;
	cout << pf() << (*pf)() << endl;

	// int (*&)()
	int (*&pfr)() = pf;
	cout << pfr << endl;

	// char *(*)(char *, char *)
	char szBuf[] = "Hello";
	char* (*pfpszfn)(char*, char*) = myPszFn;
	cout << pfpszfn << endl;
	cout << pfpszfn(szBuf,szBuf) << endl;

    pfpszfn = [](char *l, char *r) { return const_cast<char *>("foo"); };
	// 
	// second set
	// 

	// int A::*
	int A::*pmemint = &A::x_;
	int iTestPmemint = a.*pmemint;
	cout << "iTestPmemint: " << iTestPmemint << endl;
	cout << endl;

	// int (A::*)(int *)
	int (A::*pmemfnpi)(int *) = &A::fnpi;
	cout << "(a.*pmemfnpi)(&i)  : " << (a.*pmemfnpi)(&i)   << endl;
	cout << "(pa->*pmemfnpi)(&i): " << (pa->*pmemfnpi)(&i) << endl;
    std::function<int(A &, int *)> sf{&A::fnpi};
    cout << sf(a, &i) << endl;
	cout << endl;

	// int (A::**)(int *)
	int (A::**ppmemfnpi)(int *) = &pmemfnpi;
	cout << "ppmemfnpi          : " << ppmemfnpi           << endl;
	cout << "(a.**ppmemfnpi)(&i): " << (a.**ppmemfnpi)(&i) << endl;
	cout << endl;

	// int (A::*&)(int *)
	int (A::*&prmemfnpi)(int *) = pmemfnpi;
	cout << "prmemfnpi         : " << prmemfnpi          << endl;
	cout << "(a.*prmemfnpi)(&i): " << (a.*prmemfnpi)(&i) << endl;
	cout << endl;

	// double (A::*)(double (*)(float &))
	double (A::*pweirdmemfn)(double (*)(float &)) = &A::fntakingfn;
	cout << "pweirdmemfn: " << pweirdmemfn << endl;
	cout << (a.*pweirdmemfn)(myDoubleReturningFunction) << endl;
	cout << endl;
	
	// void (*p[10]) (void (*)() );
	void (*pbunchoffntakingfns[10]) (void (*)() ) = { myVoidFnTakingVoidFn, myVoidFnTakingVoidFn }; // don't need to fill remaining 8.
	cout << pbunchoffntakingfns    << endl;
	cout << pbunchoffntakingfns[0] << endl;
	pbunchoffntakingfns[0](myVoidFn);
    pbunchoffntakingfns[3] = myVoidFnTakingVoidFn;
	cout << endl;

	cout << "Finished second set." << endl;

	return 0;
}

