#include <iostream>
#include <sstream>
#include <vector>

#include <cmath>

std::string prime_factor(unsigned x) {
    std::stringstream out;

  // YOUR CODE GOES HERE
  if (x < 2) {
      out << x;
  }
  else {
      unsigned pow = 0;
      bool hflag = false;
      for (unsigned pr = 2; pr <= x; pr++) {
          while (x % pr == 0) {
              pow++;
              x = x / pr;
          }
          if (pow > 0) {
              if (hflag)
                  out << " x ";
              else
                  hflag = true;
              out << pr;
              if (pow > 1) 
                  out << "^" << pow;
              pow = 0;
          }
      }
  }
  return out.str();
}


int main() {

  auto input = 9;
  auto output = prime_factor(input);

  std::cout << "Prime factorization of " << input << " is " << output
            << std::endl;
  // expected output: 3^2

  input = 240;
  output = prime_factor(input);

  std::cout << "Prime factorization of " << input << " is " << output
            << std::endl;
  // expected output: 2^4 x 3 x 5

  input = 2;
  output = prime_factor(input);

  std::cout << "Prime factorization of " << input << " is " << output
            << std::endl;
  // expected output: 2

  input = 4;
  output = prime_factor(input);

  std::cout << "Prime factorization of " << input << " is " << output
            << std::endl;
  // expected output: 2^2

  input = 60;
  output = prime_factor(input);

  std::cout << "Prime factorization of " << input << " is " << output
            << std::endl;
  // expected output: 2^2 x 3 x 5

  input = 8320;
  output = prime_factor(input);

  std::cout << "Prime factorization of " << input << " is " << output
            << std::endl;
  // expected output: idk

  input = 9997;
  output = prime_factor(input);

  std::cout << "Prime factorization of " << input << " is " << output
            << std::endl;
  // expected output: idk

  input = 97;
  output = prime_factor(input);

  std::cout << "Prime factorization of " << input << " is " << output
            << std::endl;
  // expected output: 97

  input = 540;
  output = prime_factor(input);

  std::cout << "Prime factorization of " << input << " is " << output
            << std::endl;
  // expected output: 2^2 x 3^3 x 5

  input = 964311731;
  output = prime_factor(input);

  std::cout << "Prime factorization of " << input << " is " << output
            << std::endl;
  // expected output: idk

  input = 964311732;
  output = prime_factor(input);

  std::cout << "Prime factorization of " << input << " is " << output
            << std::endl;
  // expected output: idk

  input = 964319912;
  output = prime_factor(input);

  std::cout << "Prime factorization of " << input << " is " << output
            << std::endl;
  // expected output: idk

  return 0;
}
