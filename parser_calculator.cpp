
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <cctype>
#include <stdexcept>
#include <vector>

class Expression {
public:
    virtual ~Expression() = default;
    virtual double evaluate() const = 0;
};

class Constant : public Expression {
    double value;
public:
    explicit Constant(double val) : value(val) {}
    double evaluate() const override { return value; }
};

class Add : public Expression {
    std::unique_ptr<Expression> lhs, rhs;
public:
    Add(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : lhs(std::move(l)), rhs(std::move(r)) {}
    double evaluate() const override {
        return lhs->evaluate() + rhs->evaluate();
    }
};

class Multiply : public Expression {
    std::unique_ptr<Expression> lhs, rhs;
public:
    Multiply(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : lhs(std::move(l)), rhs(std::move(r)) {}
    double evaluate() const override {
        return lhs->evaluate() * rhs->evaluate();
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

class Parser {
    std::istringstream input;

    char peek() {
        while (std::isspace(input.peek())) input.get();
        return input.peek();
    }

    char get() {
        while (std::isspace(input.peek())) input.get();
        return input.get();
    }

    std::unique_ptr<Expression> parsePrimary() {
        if (peek() == '-') {
            get();
            return std::make_unique<Negate>(parsePrimary());
        } else if (peek() == '(') {
            get(); // consume '('
            auto expr = parseExpression();
            if (get() != ')') throw std::runtime_error("Expected ')'");
            return expr;
        } else {
            double value;
            input >> value;
            if (input.fail()) throw std::runtime_error("Expected number");
            return std::make_unique<Constant>(value);
        }
    }

    std::unique_ptr<Expression> parseTerm() {
        auto node = parsePrimary();
        while (peek() == '*') {
            get();
            node = std::make_unique<Multiply>(std::move(node), parsePrimary());
        }
        return node;
    }

    std::unique_ptr<Expression> parseExpression() {
        auto node = parseTerm();
        while (peek() == '+') {
            get();
            node = std::make_unique<Add>(std::move(node), parseTerm());
        }
        return node;
    }

public:
    explicit Parser(const std::string& str) : input(str) {}

    std::unique_ptr<Expression> parse() {
        return parseExpression();
    }
};

int main() {
    std::vector<std::string> test_cases = {
        "2 * (3 + 4)",
        "13.75 + 22 * 15",
        "-(3 + 1) * 2"
    };

    for (const auto& expr_str : test_cases) {
        try {
            Parser parser(expr_str);
            auto expr = parser.parse();
            std::cout << expr_str << " = " << expr->evaluate() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error parsing "" << expr_str << "": " << e.what() << std::endl;
        }
    }

    return 0;
}
