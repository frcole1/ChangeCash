#ifndef COIN_H
#define COIN_H

class Coin {
public:
  Coin();
  Coin(double v);

  double getValue() const { return value; }
  void setValue(double value) { value = value; }

  int getCount() const { return count; }
  void setCount(int value) { count = value; }

private:
  double value;
  int count;
};

#endif // COIN_H
