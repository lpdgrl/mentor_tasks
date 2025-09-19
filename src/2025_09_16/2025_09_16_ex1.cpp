#include <iostream>
#include <string>

using namespace std::literals;

class A {
public:
    A() : A("A object"s) {}

    virtual void Foo() const {
        std::cout << "A::foo" << std::endl;
    }

    static void Bar(const A& c, A* a) {
        c.Print();
        
        if (a != nullptr) {
            a->Foo();
        }
    }

    virtual void Print() const {
        std::cout << "I am A" << std::endl;
    }

    virtual ~A() = default; // деструктор виртуальный, чтобы можно было удалить объект через указатель на базовый класс

private:
    A(std::string name_object) : name_object_{std::move(name_object)} {}

private:
    std::string name_object_;
};

class B final : public A {
    void Foo() const override {
        std::cout << "B::foo" << std::endl;
    }
    void Print() const override {
        std::cout << "I am B" << std::endl;
    }
};

class C final : public A {
    void Foo() const override {
        std::cout << "C::foo" << std::endl;
    }
};

int main() {
    A* a = new B();
    A* c = new C();

    a->Foo();
    c->Foo();

    A::Bar(*a, c);
    return 0;
}