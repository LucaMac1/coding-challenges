#include <iostream>
#include <memory>

// Abstract base class
class Expression {
public:
    virtual double evaluate() const = 0;
    virtual ~Expression() = default;
};

// Constant (leaf node)
class Constant : public Expression {
    double value;
public:
    explicit Constant(double val) : value(val) {}
    double evaluate() const override {
        return value;
    }
};

// Addition (binary node)
class Add : public Expression {
    std::unique_ptr<Expression> left, right;
public:
    Add(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : left(std::move(l)), right(std::move(r)) {}
    
    double evaluate() const override {
        return left->evaluate() + right->evaluate();
    }
};

// Subtraction (binary node)
class Subtract : public Expression {
    std::unique_ptr<Expression> left, right;
public:
    Subtract(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : left(std::move(l)), right(std::move(r)) {}
    
    double evaluate() const override {
        return left->evaluate() - right->evaluate();
    }
};

// Multiplication (binary node)
class Multiply : public Expression {
    std::unique_ptr<Expression> left, right;
public:
    Multiply(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : left(std::move(l)), right(std::move(r)) {}
    
    double evaluate() const override {
        return left->evaluate() * right->evaluate();
    }
};

// Division (binary node)
class Divide : public Expression {
    std::unique_ptr<Expression> left, right;
public:
    Divide(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : left(std::move(l)), right(std::move(r)) {}
    
    double evaluate() const override {
        double right_value = right->evaluate();
        if (right_value == 0) {
            throw std::runtime_error("Error: Division by zero.");
        }
        return left->evaluate() / right_value;
    }
};

class Negate : public Expression {
    std::unique_ptr<Expression> operand;
public:
    explicit Negate(std::unique_ptr<Expression> expr)
        : operand(std::move(expr)) {}

    double evaluate() const override {
        return -operand->evaluate();
    }
};

// Test expressions
int main() {
    try {
        // Expression: 2 * (3 + 4)
        std::unique_ptr<Expression> expr1 = std::make_unique<Multiply>(
            std::make_unique<Constant>(2),
            std::make_unique<Add>(
                std::make_unique<Constant>(3),
                std::make_unique<Constant>(4)
            )
        );
        std::cout << "2 * (3 + 4) = " << expr1->evaluate() << std::endl;

        // Expression: 13.75 + 22 * 15
        std::unique_ptr<Expression> expr2 = std::make_unique<Add>(
            std::make_unique<Constant>(13.75),
            std::make_unique<Multiply>(
                std::make_unique<Constant>(22),
                std::make_unique<Constant>(15)
            )
        );
        std::cout << "13.75 + 22 * 15 = " << expr2->evaluate() << std::endl;

        // New Expression: 10 - 3 * 2
        std::unique_ptr<Expression> expr3 = std::make_unique<Subtract>(
            std::make_unique<Constant>(10),
            std::make_unique<Multiply>(
                std::make_unique<Constant>(3),
                std::make_unique<Constant>(2)
            )
        );
        std::cout << "10 - 3 * 2 = " << expr3->evaluate() << std::endl;

        // New Expression: 10 / 2 + 5
        std::unique_ptr<Expression> expr4 = std::make_unique<Add>(
            std::make_unique<Divide>(
                std::make_unique<Constant>(10),
                std::make_unique<Constant>(2)
            ),
            std::make_unique<Constant>(5)
        );
        std::cout << "10 / 2 + 5 = " << expr4->evaluate() << std::endl;

        // Optional unary operator: -4
        std::unique_ptr<Expression> expr5 = std::make_unique<Negate>(
            std::make_unique<Constant>(4)
        );
        std::cout << "-4 = " << expr5->evaluate() << std::endl;

        // Edge case: Division by zero
        std::unique_ptr<Expression> expr6 = std::make_unique<Divide>(
            std::make_unique<Constant>(10),
            std::make_unique<Constant>(0)
        );
        std::cout << "10 / 0 = " << expr6->evaluate() << std::endl; // This should throw an error

    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}