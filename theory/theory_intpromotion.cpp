#include <iostream>
using namespace std;

// Helper to show type + value
#define SHOW(x)  cout << #x << " → " << (x) << "   [type: " << typeid(x).name() << "]\n"

int main()
{
    // ────────────────────────────────────────────────
    // 1. char → int promotion (very common source of surprise)
    // ────────────────────────────────────────────────
    char a = 100;
    char b = 40;
    auto sum1 = a + b;           // promoted to int + int → int
    SHOW(sum1);                  // 140    [type: i]

    char c = 100;
    char d = 160;                // 160 > 127 → implementation-defined (usually -96 on 2's complement)
    auto sum2 = c + d;
    SHOW(sum2);                  // usually 4 or 260 depending on signedness & wrap behavior

    // ────────────────────────────────────────────────
    // 2. unsigned char stays unsigned char? → NO!
    // ────────────────────────────────────────────────
    unsigned char uc = 200;
    unsigned char ud = 100;
    auto sum3 = uc + ud;         // → int + int  (usual arithmetic conversions)
    SHOW(sum3);                  // 300   [type: i]     ← surprise!

    // But this stays unsigned:
    auto sum4 = +uc + +ud;       // unary + forces promotion → still int
    auto sum5 = uc + 0u;         // unsigned int + unsigned char → unsigned int
    SHOW(sum5);                  // 300   [type: j or Kj etc.]

    // ────────────────────────────────────────────────
    // 3. Classic signed/unsigned comparison + addition trap
    // ────────────────────────────────────────────────
    int          si = -1;
    unsigned int ui = 1;

    auto r1 = si + ui;           // int + unsigned int → unsigned int
    SHOW(r1);                    // huge number (UINT_MAX)   ← very common bug!

    bool is_positive = (si + ui) > 0;   // true (because unsigned)
    cout << boolalpha << "is_positive = " << is_positive << "\n\n";

    // ────────────────────────────────────────────────
    // 4. short + short → int   (almost nobody expects this)
    // ────────────────────────────────────────────────
    short s1 = 30000;
    short s2 = 8000;

    auto sum_short = s1 + s2;          // int + int !
    SHOW(sum_short);                   // 38000   [type: i]

    // But this can overflow before promotion:
    short s3 = 30000;
    short s4 = 30000;
    short bad = s3 + s4;               // undefined behavior! (overflow in short before assignment)

    // Safer:
    int safe = s3 + s4;                // ok – promotes first

    // ────────────────────────────────────────────────
    // 5. char literal + something
    // ────────────────────────────────────────────────
    auto weird1 = 'A' + 1;             // int('A') + 1 → int   ('B')
    auto weird2 = true + 'A';          // 1 + 65 → int 66 ('B')
    auto weird3 = 'A' + true + 2u;     // (int + int → int) + unsigned → unsigned

    SHOW(weird1);
    SHOW(weird2);
    SHOW(weird3);

    // ────────────────────────────────────────────────
    // 6. Very nasty one-liner that appears in real bugs
    // ────────────────────────────────────────────────
    unsigned char pixels[4] = {255, 255, 255, 128};
    int brightness = pixels[0] + pixels[1] + pixels[2] + pixels[3];
    // What is brightness?  →  733     (not 255*3+128=893 !)

    // Because each addition promotes → int
    // But many people think it stays in unsigned char → WRONG

    cout << "\nbrightness = " << brightness << "   (expected 893 by many beginners)\n";

    // Correct (if you really want 8-bit saturated add):
    int brightness2 = 0u + pixels[0] + pixels[1] + pixels[2] + pixels[3];

    // ────────────────────────────────────────────────
    // 7. Enum + int   (C++11 scoped enum behaves differently)
    // ────────────────────────────────────────────────
    enum Color  { RED = 0xFF0000, GREEN = 0x00FF00 };
    enum class Color2 { RED = 0xFF0000, GREEN = 0x00FF00 };

    auto e1 = RED    + 1;              // ok – enum → int
    // auto e2 = Color2::RED + 1;      // ERROR – scoped enum does NOT promote

    SHOW(e1);

    return 0;
}
