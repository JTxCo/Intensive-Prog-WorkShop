#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <random>
#include <climits>
#include <cstdlib>
using namespace std;

const char *PASSWORD_FILE = "rictro";

void exploreMe(int a, int b, string c) {
    // printf("a: %d; b: %d; c: %s\n", a, b, c.c_str());

    if (a >= 20000) {
      if (b >= 2000000) {
        if (b - a < 100000) {
          int n = 23;
          n <<= 32;
          if (c == "abcd") {
            // heap overflow example
            std::cout << "heap overflow!!" << std::endl;
            char *s = (char *)malloc(1);
            strcpy(s, "too long");
            // stack overflow example
            //break the stack
            int arr[1000000];
            arr[1000000] = 1;
          }
        }
      }
    }
}


void fuzzTest() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_int(0, INT_MAX);
    std::uniform_int_distribution<> dis_str_len(0, 10);

    for (int i = 0; i < 100000000; i++) {
        int a = dis_int(gen);
        int b = dis_int(gen);
        std::string c;
        for (int j = 0; j < dis_str_len(gen); j++) { 
            c += static_cast<char>(dis_int(gen) % 26 + 'a');
            cout<<c<<endl;
        }

        try {
            exploreMe(a, b, c);
        } catch (const std::exception& e) {
            std::cout << "Error for inputs: " << a << ", " << b << ", " << c << std::endl;
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }
}

int main()
{
  // stack buffer overflow example (with certain inputs)
  char input[8];
  char password[8];

  std::sscanf(PASSWORD_FILE, "%s", password);

  std::cout << "Enter password: ";
  std::cin >> input;

  if (std::strncmp(password, input, 8) == 0)
    std::cout << "Access granted\n";
  else
    std::cout << "Access denied\n";

  fuzzTest();

  return 0;
}
