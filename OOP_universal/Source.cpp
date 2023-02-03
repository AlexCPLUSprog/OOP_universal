#include <iostream>
#include<map>
#include<vector>
#include<algorithm>
// lvalue, rvalue ссылки
// универсальные ссылки

int foo() {
	return 2;
}

int globalvalue = 20;

int& bar() {		// int& - ссылка на тип возвращаемого значени€
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

	IntVec& operator=(IntVec&& other) noexcept {		// ссылка на rvalue
		// оператор присваивани€ перемещением
		log("move assignment operator");
		std::swap(m_size, other.m_size);
		std::swap(m_data, other.m_data);
		return *this;
	}



	// c1 = c2
	IntVec& operator=(const IntVec& other) {
		// оператор присваивани€ копированием
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
	// c_aFunc().foo();	// cv-квалифицированный rvalue

	// lvalue (locator value) представл€ет собой объект, который занимает идентифицируемое место в пам€ти (например, имеет адрес).
	// rvalue Ч это выражение, которое не представл€ет собой объект, который занимает идентифицируемое место в пам€ти.

	int x = 5;
	// foo() = 2;
	bar() = 10;

	std::map<int, float> mymap;
	mymap[10] = 5.6f;	// operator[] внутри класса std::map, который вернул ссылку на объект, который можно измен€ть

	const int a = 10;	// lvalue, обратитьс€ к нему можем, но помен€ть нет, ибо константа
	// a = 11;

	int t = 1;
	int tt = 2;
	int res = t + tt;	// operator+ ожидает rvalue, поэтому lvalue не€вно преобразуетс€ в rvalue
	// не€вного обратного преобразовани€ быть не может

	int arr[] = { 1,2 };
	int* p = &arr[0];
	 *(p + 1) = 10;	// €вное преобразование rvalue (p + 1) в lvalue с помощью *			// *(p + 1) - lvalue

	// lvalue в rvalue с помощью &
	int var = 10;
	// int& bad_addr = &(var + 1);	// ошибка: дл€ унарного оператора & требуетс€ lvalue

	int* addr = &var;	// ok
	// &var = 40; // error, с левой стороны требуетс€ lvalue
	
	// —ам адрес не имеет идентифицируемого места в пам€ти

	// lvalue на тип “, не €вл€ющимс€ функциональным или массивом, может быть преобразован в rvalue, <...>
	// ≈сли “ не класс, типом rvalue €вл€етс€ cv-неспецифицированна€ верси€ типа “. »наче, типом rvalue €вл€етс€ “
	// cv: c - const, v - volatile

	// T lvalue -> T rvalue 
	// const volatile T lvalue -> T rvalue 

	// ≈сли “ - это класс, то rvalue может сохранить cv-специфицированность(тот тип, который может быть и константным и волатильным)

	// v - volatile (может мен€тьс€ в любой момент)

	std::vector<int> qwe;

	for (size_t i = 0; i < qwe.size(); i++) {	// qwe.size() не волатильный, не будем измен€ть вообще
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
	v3 = std::move(v1);	// опасна€ и полезна€ функци€, превращающает lvalue в rvalue  // == IntVec& operator=(IntVec&& v1) {...}	// v3.operator=(std::move(v1))
	std::cout << "ended assigning rvalue...\n";
}



