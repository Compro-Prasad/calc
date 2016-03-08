#include <stdio.h>
#include <math.h>
#define sin(x) var(sin(x.val))
#define cos(x) var(cos(x.val))
#define tan(x) var(tan(x.val))
#define cosec(x) var((1 / sin(x.val)))
#define sec(x) var((1 / cos(x.val)))
#define cot(x) var((1/ tan(x.val)))
#define logten(x) var(log10(x.val))
#define ln(x) var(log(x.val, 2.71))
#define log(x, y) var((log(x) / log(y)))
#define abs(x) var(abs(x.val))
#define ceil(x) var(ceil(x.val))
#define floor(x) var(floor(x.val))
#define asin(x) var(asin(x.val))
#define acos(x) var(acos(x.val))
#define atan(x) var(atan(x.val))
#define acosec(x) var(asin(1 / x.val))
#define asec(x) var(acos(1 / x.val))
#define acot(x) var(atan(1 / x.val))
/*template <typename T>
  var sin(T x)
{
*/
struct var
{
  long double val;
  var()
  {
    val = 0.0;
  }
  var(long double x)
  {
    val = x;
  }
  var operator=(long double x)
  {
    val = x;
  }
  var operator=(var x)
  {
    val = x.val;
  }
  var operator+(long double x)
  {
    var y = val + x;
    return y;
  }
  var operator+(var x)
  {
    var y = val + x.val;
    return y;
  }
  var operator-(long double x)
  {
    var y = val - x;
    return y;
  }
  var operator-(var x)
  {
    var y = val - x.val;
    return y;
  }
  var operator*(long double x)
  {
    var y = val * x;
    return y;
  }
  var operator/(long double x)
  {
    var y = val * x;
    return y;
  }
  var operator/(var x)
  {
    var y = val * x.val;
    return y;
  }
  var operator%(long double x)
  {
    var y = fmod(val, x);
    return y;
  }
  var operator%(var x)
  {
    var y = fmod(val, x.val);
    return y;
  }
  var operator!()
  {
    var f = 1, i = 1;
    for (; i.val <= val; i.val++)
      f.val *= i.val;
    return f;
  }
  var operator>>(long x)
  {
    var y = (long)val >> x;
    return y;
  }
  var operator>>(var x)
  {
    var y = (long)val >> (long)x.val;
    return y;
  }
  var operator<<(long x)
  {
    var y = (long)val << x;
    return y;
  }
  var operator<<(var x)
  {
    var y = (long)val << (long)x.val;
    return y;
  }
  var operator~()
  {
    var y = ~(long)val;
    return y;
  }
  var operator|(long x)
  {
    var y = (long)val | x;
    return y;
  }
  var operator|(var x)
  {
    var y = (long)val | (long)x.val;
    return y;
  }
  var operator&(long x)
  {
    var y = (long)val & x;
    return y;
  }
  var operator&(var x)
  {
    var y = (long)val & (long)x.val;
    return y;
  }
  var operator^(long double x)
  {
    var y = pow(val, x);
    return y;
  }
  var operator^(var x)
  {
    var y = pow(val, x.val);
    return y;
  }
  var operator()(long double x)
  {
    var y = x;
    return y;
  }
};
/*
int f(var x, var y, var z)
{
  x = sin(cos(ln(x)));
  printf("x = %Lf\n", x.val);
  return 0;
}

int main()
{
  f(2, 3, 4);
  return 0;
}
*/
