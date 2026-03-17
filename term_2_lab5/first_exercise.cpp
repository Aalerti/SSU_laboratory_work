#include <iostream>
#include <fstream>
#include <stack>

bool is_consonant(char c) {
  if (!std::isalpha(c))
    return false;

  char lower_char = std::tolower(c);
  bool is_vowel = (lower_char == 'a' || lower_char == 'e' || lower_char == 'i' ||
                  lower_char == 'o' || lower_char == 'u' || lower_char == 'y');

  return !is_vowel;
}

void print_stack(std::stack<char> &letters) {
  while (!letters.empty()) {
    std::cout << letters.top() << ' ';
    letters.pop();
  }
}

int main() {
  int n;
  std::cin >> n;

  std::stack<char> letters;
  int index_of_first_consonant = -1;

  for (int i = 0; i < n; i++) {
    char c;
    std::cin >> c;
    if (is_consonant(c) && index_of_first_consonant == -1) {
      index_of_first_consonant = i;
    }
    letters.push(c);
  }

  if (index_of_first_consonant == -1) {
    print_stack(letters);
    return 0;
  }

  // Если нужно чтобы выводился красивый порядок то
  std::stack<char> temp_stack;
  int current_index = n-1;
  while (!letters.empty()) {
    if (current_index == index_of_first_consonant) {
      temp_stack.push('!');
    }
    temp_stack.push(letters.top());
    letters.pop();
    current_index--;
  }
  print_stack(temp_stack);

  // std::stack<char> temp_stack;
  // while (!letters.empty()) {
  //   temp_stack.push(letters.top());
  //   letters.pop();
  // }
  //
  // std::stack<char> new_stack;
  // int current_index = 0;
  //
  // while (!temp_stack.empty()) {
  //   new_stack.push(temp_stack.top());
  //   temp_stack.pop();
  //
  //
  //   if (current_index == index_of_first_consonant) {
  //     new_stack.push('!');
  //   }
  //   current_index++;
  // }
  //
  // print_stack(new_stack);

  return 0;
}