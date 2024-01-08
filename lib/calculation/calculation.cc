#include "calculation.h"

Calculation::fun_ptr_t Calculation::m_fun_ptr = {
    {'(', {"(", {f_prt_t::DEFAULT, nullptr}}},
    {'+', {"+", {f_prt_t::L_PR, std::plus<double>()}}},
    {'-', {"-", {f_prt_t::L_PR, std::minus<double>()}}},
    {'*', {"*", {f_prt_t::M_PR, std::multiplies<double>()}}},
    {'/', {"/", {f_prt_t::M_PR, std::divides<double>()}}},
    {'A', {"mod", {f_prt_t::M_PR, static_cast<fcast_2arg>(&std::fmod)}}},
    {'^', {"^", {f_prt_t::H_PR, static_cast<fcast_2arg>(&std::pow)}}},
    {'B', {"B", {f_prt_t::UNARY, nullptr}}},
    {'C', {"C", {f_prt_t::UNARY, std::negate<double>()}}},
    {'D', {"acos", {f_prt_t::FUNC, static_cast<fcast_1arg>(&std::acos)}}},
    {'E', {"asin", {f_prt_t::FUNC, static_cast<fcast_1arg>(&std::asin)}}},
    {'F', {"atan", {f_prt_t::FUNC, static_cast<fcast_1arg>(&std::atan)}}},
    {'G', {"cos", {f_prt_t::FUNC, static_cast<fcast_1arg>(&std::cos)}}},
    {'H', {"sin", {f_prt_t::FUNC, static_cast<fcast_1arg>(&std::sin)}}},
    {'I', {"tan", {f_prt_t::FUNC, static_cast<fcast_1arg>(&std::tan)}}},
    {'J', {"sqrt", {f_prt_t::FUNC, static_cast<fcast_1arg>(&std::sqrt)}}},
    {'K', {"ln", {f_prt_t::FUNC, static_cast<fcast_1arg>(&std::log)}}},
    {'L', {"log", {f_prt_t::FUNC, static_cast<fcast_1arg>(&std::log10)}}}};

auto Calculation::expression_load(QString infix) -> void {
  m_rpn.clear();
  if (expression_validate(infix)) {
    expression_up(infix);
    QStack<QChar> stack;
    for (qsizetype i = 0; i < infix.size(); ++i) {
      if (infix[i] == 'x') {
        m_rpn.push_back(infix[i]);
      } else if (infix[i] == 'p') {
        m_rpn.push_back(M_PI);
      } else if (infix[i] == 'e') {
        m_rpn.push_back(M_E);
      } else if (infix[i].isDigit()) {
        qstrtod(infix, i);
      } else if (is_function(infix[i])) {
        stack.push(infix[i]);
      } else if (is_operation(infix[i])) {
        while (!stack.isEmpty() && is_operation(stack.top()) && is_priority_le(infix[i], stack.top())) {
          m_rpn.push_back(stack.pop());
        }
        stack.push(infix[i]);
      } else if (infix[i] == '(') {
        stack.push(infix[i]);
      } else if (infix[i] == ')') {
        while (stack.top() != '(') {
          m_rpn.push_back(stack.pop());
        }
        stack.pop();
        if (!stack.isEmpty() && is_function(stack.top())) {
          m_rpn.push_back(stack.pop());
        }
      }
    }
    while (!stack.isEmpty()) {
      m_rpn.push_back(stack.pop());
    }
  }
}

auto Calculation::calculation(double x) -> double {
  QStack<double> stack;
  for (auto it : m_rpn) {
    std::visit(overloaded{[&](QChar& arg) {
                            if (arg == 'x') {
                              stack.push(x);
                            } else {
                              std::visit(
                                  overloaded{[&](fp_1arg fn) {
                                               stack.push(fn(stack.pop()));
                                             },
                                             [&](fp_2arg fn) {
                                               double rhs = stack.pop();
                                               double lhs = stack.pop();
                                               stack.push(fn(lhs, rhs));
                                             },
                                             []([[maybe_unused]] auto fn) {}},
                                  m_fun_ptr.value(arg).second.second);
                            }
                          },
                          [&](double& arg) { stack.push(arg); }},
               it);
  }
  return stack.pop();
}

auto Calculation::expression_up(QString& infix) -> void {
  for (auto it = m_fun_ptr.begin(); it != m_fun_ptr.end(); ++it) {
    infix.replace(it.value().first, it.key());
  }
  static const QHash<QRegularExpression, QString> rgx_table{
      {QRegularExpression("([+\\-*\\/^\\(A])([\\+])"), "\\1B"},
      {QRegularExpression("([+\\-*\\/^\\(A])([\\-])"), "\\1C"},
      {QRegularExpression("^[\\+]"), "B"},
      {QRegularExpression("^[\\-]"), "C"},
  };
  for (auto it = rgx_table.begin(); it != rgx_table.end(); ++it) {
    infix.replace(it.key(), it.value());
  }
}

auto Calculation::expression_validate(QString& infix) -> bool {
  static const QVector<QRegularExpression> regex{
      QRegularExpression(".(?<![+\\-*\\/^(.]|mod|\\d)(\\d)"),
      QRegularExpression("(?<![)xpe]|\\d)([\\*\\/^]|mod)"),
      QRegularExpression("(?<![)xpe]|\\d)([+\\-\\*\\/^]|mod)([+-])"),
      QRegularExpression(".(?<![())xpe+\\-\\*\\/^E]|\\d|mod)([+-])"),
      QRegularExpression("(?<=^|[-+*\\/^(]|mod)(ln|log|sqrt|a?(cos|sin|tan))(*SKIP)(*F)|(?1)"),
      QRegularExpression("(\\((?>[^()\n]|(?1))*+\\))(*SKIP)(*F)|[()]"),
      QRegularExpression(".(?<![+\\-*\\/^(sntgd])[(]"),
      QRegularExpression("(?<!\\d|[)xpe])[)]"),
      QRegularExpression("\\d*?[.]\\d*?[.]\\d*?"),
      QRegularExpression(".(?<!\\d|[\\)xpe])$"),
      QRegularExpression("(?<!\\d)E"),
      QRegularExpression("nan|inf")};
  bool flag = true;
  for (auto it : regex) {
    if (infix.contains(it)) {
      flag = false;
      break;
    }
  }
  return flag;
}

auto Calculation::is_function(QChar& lexem) -> bool {
  bool flag = false;
  if (m_fun_ptr.contains(lexem)) {
    if (get_priority(lexem) == f_prt_t::FUNC) {
      flag = true;
    }
  }
  return flag;
}

auto Calculation::is_operation(QChar& lexem) -> bool {
  bool flag = false;
  if (m_fun_ptr.contains(lexem)) {
    if (get_priority(lexem) > f_prt_t::DEFAULT &&
        get_priority(lexem) < f_prt_t::FUNC) {
      flag = true;
    }
  }
  return flag;
}

auto Calculation::get_priority(QChar& lexem) -> Calculation::f_prt_t {
  return m_fun_ptr.value(lexem).second.first;
}

auto Calculation::is_priority_le(QChar& lhs, QChar& rhs) -> bool {
  bool flag = false;
  if (get_priority(lhs) <= get_priority(rhs)) {
    flag = true;
  }
  return flag;
}

auto Calculation::qstrtod(QString& src, qsizetype& ind) -> void {
  static const QRegularExpression regex("\\d+(([.]\\d+)?(E[+-]\\d+)?)?");
  QRegularExpressionMatch match = regex.match(src, ind);
  if (match.capturedStart(0) == ind) {
    m_rpn.push_back(match.captured(0).toDouble());
    ind += (match.capturedLength() - 1);
  }
}

auto Calculation::is_empty() -> bool { return m_rpn.empty(); }

#ifdef __cplusplus
extern "C" {
#endif
auto _Calculation__create() -> Calculation * {
  return new Calculation();
}

auto _Calculation__remove(Calculation* instance) -> void {
  delete instance;
}

auto _Calculation__load(Calculation* instance, const char* infix) -> void {
  instance->expression_load(QString::fromUtf8(infix));
}

auto _Calculation__calc(Calculation* instance, double x) -> double {
  return instance->calculation(x);
}

auto _Calculation__empty(Calculation* instance) -> bool {
  return instance->is_empty();
}
#ifdef __cplusplus
}
#endif
