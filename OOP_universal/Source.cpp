#include <iostream>
#include<map>
#include<vector>
#include<algorithm>
// lvalue, rvalue ������
// ������������� ������

int foo() {
	return 2;
}

int globalvalue = 20;

int& bar() {		// int& - ������ �� ��� ������������� ��������
	return globalvalue;
}

/*class A {
public:
	void foo() const {
		std::cout << "A::foo() const\n";
	}
	void foo() {
		std::cout << "A::foo()\n";
	}

};

A aFunc() {
	return A();
}

const A c_aFunc() {
	return A();
}*/

// Intvec v1 = 20; 
// Intvec v1(20);	

class IntVec {
public:
	explicit IntVec(size_t num = 0) : m_size(num), m_data(new int[m_size]) {
		log("constructor");
	}

	~IntVec() {
		log("destructor");
		if (m_data) {
			delete[] m_data;
			m_data = 0;
		}
	}

	IntVec(const IntVec& other) : m_size(other.m_size), m_data(new int[m_size]) {
		log("copy constructor");
		for (size_t i = 0; i < m_size; i++) {
			m_data[i] = other.m_data[i];
		}
	}

	IntVec& operator=(IntVec&& other) noexcept {		// ������ �� rvalue
		// �������� ������������ ������������
		log("move assignment operator");
		std::swap(m_size, other.m_size);
		std::swap(m_data, other.m_data);
		return *this;
	}



	// c1 = c2
	IntVec& operator=(const IntVec& other) {
		// �������� ������������ ������������
		log("copy assignment operator");
		IntVec tmp(other);
		std::swap(m_size, tmp.m_size);	// copy-swap idioma
		std::swap(m_data, tmp.m_data);
		return *this;
	}

private:
	void log(const char* msg) {
		std::cout << "[" << this << "]" << msg << '\n';
	}

	size_t m_size;
	int* m_data;
};


int main() {

	// aFunc().foo();
	// c_aFunc().foo();	// cv-����������������� rvalue

	// lvalue (locator value) ������������ ����� ������, ������� �������� ���������������� ����� � ������ (��������, ����� �����).
	// rvalue � ��� ���������, ������� �� ������������ ����� ������, ������� �������� ���������������� ����� � ������.

	int x = 5;
	// foo() = 2;
	bar() = 10;

	std::map<int, float> mymap;
	mymap[10] = 5.6f;	// operator[] ������ ������ std::map, ������� ������ ������ �� ������, ������� ����� ��������

	const int a = 10;	// lvalue, ���������� � ���� �����, �� �������� ���, ��� ���������
	// a = 11;

	int t = 1;
	int tt = 2;
	int res = t + tt;	// operator+ ������� rvalue, ������� lvalue ������ ������������� � rvalue
	// �������� ��������� �������������� ���� �� �����

	int arr[] = { 1,2 };
	int* p = &arr[0];
	 *(p + 1) = 10;	// ����� �������������� rvalue (p + 1) � lvalue � ������� *			// *(p + 1) - lvalue

	// lvalue � rvalue � ������� &
	int var = 10;
	// int& bad_addr = &(var + 1);	// ������: ��� �������� ��������� & ��������� lvalue

	int* addr = &var;	// ok
	// &var = 40; // error, � ����� ������� ��������� lvalue
	
	// ��� ����� �� ����� ����������������� ����� � ������

	// lvalue �� ��� �, �� ���������� �������������� ��� ��������, ����� ���� ������������ � rvalue, <...>
	// ���� � �� �����, ����� rvalue �������� cv-������������������� ������ ���� �. �����, ����� rvalue �������� �
	// cv: c - const, v - volatile

	// T lvalue -> T rvalue 
	// const volatile T lvalue -> T rvalue 

	// ���� � - ��� �����, �� rvalue ����� ��������� cv-�������������������(��� ���, ������� ����� ���� � ����������� � �����������)

	// v - volatile (����� �������� � ����� ������)

	std::vector<int> qwe;

	for (size_t i = 0; i < qwe.size(); i++) {	// qwe.size() �� �����������, �� ����� �������� ������
		/*...*/
	}
	

	IntVec v1(20);
	IntVec v2;
	IntVec v3;

	std::cout << "assigning lvalue...\n";
	v2 = v1;
	std::cout << "ended assigning lvalue...\n";
	std::cout << "=========================\n";
	std::cout << "assigning rvalue...\n";
	v3 = IntVec(33);
	v3 = std::move(v1);	// ������� � �������� �������, ������������� lvalue � rvalue  // == IntVec& operator=(IntVec&& v1) {...}	// v3.operator=(std::move(v1))
	std::cout << "ended assigning rvalue...\n";
}



