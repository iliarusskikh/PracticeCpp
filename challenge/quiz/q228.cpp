template <typename ...Ts>
struct X {
  X(Ts ...args) : Var(0, args...) {}
  int Var;
};

int main() {
  X<> x;
}

//the program undefined
//the only valid specialization requires an empty template parameter pack, so the program is ill-formed, no diagnostic required. When no diagnostic is required, the compiler is not required to diagnose the error, but execution of the program is undefined.
