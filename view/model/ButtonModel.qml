import QtQuick

ListModel {
  ListElement {
    name: "ƒ"
    action: function () {
      graph()
    }
  }
  ListElement {
    name: "^"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "sqrt"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "AC"
    action: function (value) {
      clean()
    }
  }
  ListElement {
    name: "("
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: ")"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "÷"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "π"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "e"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "x"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "7"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "8"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "9"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "×"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "acos"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "cos"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "mod"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "4"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "5"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "6"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "-"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "asin"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "sin"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "ln"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "1"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "2"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "3"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "+"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "atan"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "tan"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "log"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "0"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "."
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "E"
    action: function (value) {
      lexeme(value)
    }
  }
  ListElement {
    name: "="
    action: function (value) {
      equal()
    }
  }

  function lexeme(value) {
    _display.text += value
  }

  function clean(value = "") {
    _display.text = value
  }

  function equal() {
    let expression = _display.text
    expression = expression.replace("÷", "/")
    expression = expression.replace("π", "p")
    expression = expression.replace("×", "*")

    Calculation.load(expression)

    if (Calculation.empty()) {
      _display.incorrect = true
    } else {
      _display.incorrect = false

      if (expression.includes("x")) {
        _variable.open()
      } else {
        clean(Calculation.calc(0.0))
      }
    }
  }

  function graph() {}
}
