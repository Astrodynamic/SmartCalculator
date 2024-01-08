#ifndef CALCULATION_H_
#define CALCULATION_H_

#include <QMap>
#include <QRegularExpression>
#include <QStack>
#include <QString>
#include <QVector>
#include <cmath>
#include <functional>
#include <string>
#include <variant>

template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

class Calculation {
 public:
  auto expression_load(QString infix) -> void;
  auto calculation(double x = 0) -> double;
  auto is_empty() -> bool;

 private:
   enum class f_prt_t {
    DEFAULT,
    L_PR,
    M_PR,
    H_PR,
    UNARY,
    FUNC,
    ALL
  };

  using fcast_1arg = double (*)(double);
  using fcast_2arg = double (*)(double, double);
  using fp_1arg = std::function<double(double)>;
  using fp_2arg = std::function<double(double, double)>;
  using fp_variant = std::variant<fp_1arg, fp_2arg, nullptr_t>;
  using fun_ptr_t = const QMap<QChar, QPair<QString, QPair<f_prt_t, fp_variant>>>;

  static fun_ptr_t m_fun_ptr;

  QVector<std::variant<QChar, double>> m_rpn;

  static auto expression_up(QString& infix) -> void;
  static auto expression_validate(QString& infix) -> bool;
  static auto is_function(QChar& lexem) -> bool;
  static auto is_operation(QChar& lexem) -> bool;
  static auto get_priority(QChar& lexem) -> f_prt_t;
  static auto is_priority_le(QChar& lhs, QChar& rhs) -> bool;

  auto qstrtod(QString& src, qsizetype& ind) -> void;
};

#endif  // CALCULATION_H_
