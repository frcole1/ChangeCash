#ifndef CASHREGISTER_H
#define CASHREGISTER_H

#include "coin.h"

class CashRegister {

public:
  enum eCoinDef { coin001, coin005, coin010, coin025, coin050, coin1 };
  enum eState {
    INICIAR,
    SAIR,
    DEPOSITAR,
    SANGRAR,
    TROCAR,
    QUANTIDADE,
    ATUALIZAR,
    INSUFICIENTE,
    QUANTSANGRAR,
    ATUSANGRAR
  };

public:
  CashRegister();

  double getChange() const { return change; }
  void setChange(double value) { change = value; }

  double getBalance() const { return balance; }
  void setBalance(double value) { balance = value; }

  int getOpState() const { return opState; }
  void setOpState(int value) { opState = value; }

  void dataSave();
  void dataLoad();

  int getCountCoin(eCoinDef e);

  void insertCoin(eCoinDef e, int count);
  void extractCoin(eCoinDef e, int count);
  void refreshBalance();
  void changeCalc(double change, int *coins1, int *coins050, int *coins025,
                  int *coins010, int *coins005, int *coins001);

private:
  Coin *c001;
  Coin *c005;
  Coin *c010;
  Coin *c025;
  Coin *c050;
  Coin *c1;

  double change;
  double balance;
  int opState;

  void loadCoin(char *ptr, char *coin);
};

#endif // CASHREGISTER_H
