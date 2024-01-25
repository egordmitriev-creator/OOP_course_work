#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

class Operation {
public:
    virtual double perform(double left, double right) const = 0;
    virtual ~Operation() {}
};

class Addition : public Operation {
public:
    double perform(double left, double right) const override {
        return left + right;
    }
};

class Subtraction : public Operation {
public:
    double perform(double left, double right) const override {
        return left - right;
    }
};

class Multiplication : public Operation {
public:
    double perform(double left, double right) const override {
        return left * right;
    }
};

class Division : public Operation {
public:
    double perform(double left, double right) const override {
        if (right == 0) {
            throw runtime_error("Деление на ноль!");
        }
        return left / right;
    }
};

class Power : public Operation {
public:
    double perform(double left, double right) const override {
        return pow(left, right);
    }
};

class ElementaryFunction {
private:
    double (*function)(double);

public:
    ElementaryFunction(double (*func)(double)) : function(func) {}
    ~ElementaryFunction(){}
    double perform(double arg) const {
        return function(arg);
    }
};

class Calculator {
public:
    double calculate(double left, const Operation& op, double right) const {
        return op.perform(left, right);
    }

    double calculateElementaryFunction(const ElementaryFunction& func, double arg) const {
        return func.perform(arg);
    }
};

int main() {
    system("clear");
    Calculator calculator;

    cout << "Выберите режим:\n1. Обычные выражения\n2. Элементарные функции\n";
    int mode;
    cin >> mode;

    if (mode == 1) {
        double operand1, operand2;
        char operation;

        cout << "Операции:\n\"+\" - сложение\n\"-\" - вычитание\n\"/\" - деление\n\"*\" - умножение\n\"^\" - возведение в степень" << endl;
        
        cout << "Введите выражение (например: 2 + 3): ";
        cin >> operand1 >> operation >> operand2;

        Operation* op;

        switch (operation) {
            case '+':
                op = new Addition();
                break;
            case '-':
                op = new Subtraction();
                break;
            case '*':
                op = new Multiplication();
                break;
            case '/':
                op = new Division();
                break;
            case '^':
                op = new Power();
                break;
            default:
                cerr << "Неподдерживаемая операция!" << endl;
                return 1;
        }

        try {
            double result = calculator.calculate(operand1, *op, operand2);
            cout << "Результат: " << result << endl;
        } catch (const runtime_error& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
        
        delete op;

    } else if (mode == 2) {
        cout << "Выберите функцию:\n1. sin\n2. cos\n3. tan\n";
        int functionChoice;
        cin >> functionChoice;

        double argument;
        cout << "Введите аргумент: ";
        cin >> argument;

        switch (functionChoice) {
            case 1: {
                ElementaryFunction sinFunction(sin);
                double sinResult = calculator.calculateElementaryFunction(sinFunction, argument);
                cout << "Результат sin: " << sinResult << endl;
                break;
            }
            case 2: {
                ElementaryFunction cosFunction(cos);
                double cosResult = calculator.calculateElementaryFunction(cosFunction, argument);
                cout << "Результат cos: " << cosResult << endl;
                break;
            }
            case 3: {
                ElementaryFunction tanFunction(tan);
                double tanResult = calculator.calculateElementaryFunction(tanFunction, argument);
                cout << "Результат tan: " << tanResult << endl;
                break;
            }
            default:
                cerr << "Неподдерживаемая функция!" << endl;
                return 1;
        }
    } else {
        cerr << "Неправильный выбор режима!" << endl;
        return 1;
    }
    
    return 0;
}