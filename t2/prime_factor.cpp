#include <iostream>
#include <sstream>
#include <vector>

#include <cmath>

std::string prime_factor(unsigned x) {
  std::stringstream out;

  // YOUR CODE GOES HERE
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
  return 0;
}
