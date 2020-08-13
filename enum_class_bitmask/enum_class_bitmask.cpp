#include "stdafx.h"
#include "enum_class_bitmask.h"
#include <iostream>

void test1()
{
  enum Color
  {
    kNone = 0,
    kRed = 1 << 0, //! 1
    kGreen = 1 << 1, //! 2
    kBlue = 1 << 2, //! 4
    kWhite = kRed | kGreen | kBlue, //! 7
  };

  // true
  Color color1 = Color::kRed;
  std::cout << (color1 & Color::kRed ? "true" : "false") << std::endl;

  // true
  Color color2 = Color::kWhite;
  std::cout << (color2 & Color::kRed ? "true" : "false") << std::endl;

  // false
  Color color3 = Color::kGreen;
  std::cout << (color3 & Color::kRed ? "true" : "false") << std::endl;

  // false
  Color color4 = Color::kBlue;
  std::cout << (color4 & Color::kRed ? "true" : "false") << std::endl;
}

void test2()
{
  enum class Color
  {
    kNone = 0,
    kRed = 1 << 0, //! 1
    kGreen = 1 << 1, //! 2
    kBlue = 1 << 2, //! 4
    kWhite = kRed | kGreen | kBlue, //! 7
  };

  // compile error.
  Color color1 = Color::kRed;
  // std::cout << (color1 & Color::kRed ? "true" : "false") << std::endl;

  // compile error.
  Color color2 = Color::kWhite;
  // std::cout << (color2 & Color::kRed ? "true" : "false") << std::endl;

  // compile error.
  Color color3 = Color::kGreen;
  // std::cout << (color3 & Color::kRed ? "true" : "false") << std::endl;

  // compile error.
  Color color4 = Color::kBlue;
  // std::cout << (color4 & Color::kRed ? "true" : "false") << std::endl;
}

void test3()
{
  color1::Color red = color1::Color::kRed;
  color1::Color green = color1::Color::kGreen;
  color1::Color blue = color1::Color::kBlue;
  color1::Color white = color1::Color::kWhite;

  auto a = static_cast<bool>(red & red);
  auto b = static_cast<bool>(green & red);
  auto c = static_cast<bool>(blue & red);
  auto d = static_cast<bool>(white & red);

  std::cout << (a ? "true" : "false") << std::endl;
  std::cout << (b ? "true" : "false") << std::endl;
  std::cout << (c ? "true" : "false") << std::endl;
  std::cout << (d ? "true" : "false") << std::endl;
}

void test4()
{
  color2::Color red = color2::Color::kRed;
  color2::Color green = color2::Color::kGreen;
  color2::Color blue = color2::Color::kBlue;
  color2::Color white = color2::Color::kWhite;

  auto a = static_cast<bool>(red & red);
  auto b = static_cast<bool>(green & red);
  auto c = static_cast<bool>(blue & red);
  auto d = static_cast<bool>(white & red);

  std::cout << (a ? "true" : "false") << std::endl;
  std::cout << (b ? "true" : "false") << std::endl;
  std::cout << (c ? "true" : "false") << std::endl;
  std::cout << (d ? "true" : "false") << std::endl;
}

int main()
{
  test1();
  test2();
  test3();
  test4();
  return 0;
}