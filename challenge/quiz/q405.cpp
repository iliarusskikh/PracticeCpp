int square(int num) {
  return num * num;
}

int main() {
  constexpr int r = square(10);
  return r;
}
// Compilation error
//This program is ill-formed, because square is not declared constexpr, yet it is invoked in the initializer of a constexpr int r variable.
