#include "performance_timings.h"
#include <chrono>
#include <iostream>
#include <objbase.h>


struct CallOnlyTests{
	static std::string Description(){return "CallOnlyTests";}

	template<class T>
	static void Run(T& t){
		t.f0();
	}


};
struct IntegerTests{
	static std::string Description(){return "IntegerTests";}

	template<class T>
	static void  Run(T& t){
		t.f1();
		t.f2(6) ;
	}
};

struct StringTestsReturnString{
	static std::string Description(){return "StringTestsReturnString";}

	template<class T>
	static void  Run(T& t){
		std::string  s;
        s= t.f3();
	}
};

struct StringTestsPassStringRef{
	static std::string Description(){return "StringTestsPassStringRef";}
    const static std::string s;
	template<class T>
	static void  Run(T& t){
		t.f4(s);
	}
};
const std::string StringTestsPassStringRef::s("Hello World");

struct StringTestsPassStringShort{
	static std::string Description(){return "StringTestsPassStringShort";}
    const static std::string s;

	template<class T>
	static void  Run(T& t){
		t.f5(s);
	}
};

const std::string StringTestsPassStringShort::s("Hello World");

struct StringTestsPassStringLong{
	static std::string Description(){return "StringTestsPassStringLong";}
    const static std::string s;

	template<class T>
	static void  Run(T& t){
		t.f5(s);
	}
};
const std::string StringTestsPassStringLong::s(1024,'a');

struct StringTestsReturnStringVsChar{
	static std::string Description(){return "StringTestsReturnStringVsChar";}

	template<class T>
	static void  Run(T& t){
        std::string s;
		s = t.f3();
	}

    static void Run(VirtualInterface& t){
        std::size_t i = 0;
        auto p = t.f6(&i);
        std::string s(p,i);
        CoTaskMemFree((void*)p);
   
    }
};
struct StringTestPassRefStringVsChar{
	static std::string Description(){return "StringTestsPassRefStringVsChar";}
        const static std::string s;

	template<class T>
	static void  Run(T& t){
        t.f4(s);
	}

    static void Run(VirtualInterface& t){
        t.f7(s.c_str(),s.size());
   
    }
};
const std::string StringTestPassRefStringVsChar::s(1024,'a');

struct StringTestOutParameter{
	static std::string Description(){return "StringTestOutParameter";}

	template<class T>
	static void  Run(T& t){
        std::string s;
		t.f8(&s);
	}
};

template<class Test,class T>
double TimingTest(T& t){

	auto begin = std::chrono::steady_clock::now();
	const int iterations = 1000000;
	for(int i = 0; i < iterations;i++){
		Test::Run(t);
	}

	auto end = std::chrono::steady_clock::now();

	auto diff = end - begin;
	return std::chrono::duration<double,std::nano>(diff).count()/iterations;


}

template<class Test,class... Tests>
struct Runner{

	template<class T>
	static void Run(std::string type, T&t){
		std::cout << "Timings for " << type << std::endl;
		RunImp(t);
		std::cout << std::endl;

	}


	template<class T>
	static void RunImp(T& t){
		auto d = TimingTest<Test>(t);
		std::cout << "   " << Test::Description() << " " << d << std::endl;
		Runner<Tests...>::RunImp(t);

	}

};

template<class Test>
struct Runner<Test>{
	template<class T>
	static void RunImp(T& t){
		auto d = TimingTest<Test>(t);
		std::cout <<  "   " << Test::Description() << " " << d << std::endl;
	}

};


int main(){

	cross_compiler_interface::module m("performance_timings_dll");

	// Virtual Function Implementation
	typedef const portable_base* (CROSS_CALL_CALLING_CONVENTION *CFun)();
	auto f = m.load_module_function<CFun>("CreateVirtualInterface");
	VirtualInterface* p = (VirtualInterface*) f();

	// std::function implementation
	use_interface<TestInterface1> t1(cross_compiler_interface::create<TestInterface1>(m,"CreateFunctionImpInterface"));

	// Member function implementation
	use_interface<TestInterface1> t2(cross_compiler_interface::create<TestInterface1>(m,"CreateMemFnImpInterface"));

	typedef Runner<CallOnlyTests,IntegerTests,StringTestsReturnString,StringTestsPassStringRef,StringTestsPassStringShort,StringTestsPassStringLong,StringTestsReturnStringVsChar,StringTestPassRefStringVsChar,
    StringTestOutParameter> TestRunner;
	TestRunner::Run("FunctionImp",t1);
	TestRunner::Run("VirtualInterface",*p);
	TestRunner::Run("MemFnImp",t2);



}