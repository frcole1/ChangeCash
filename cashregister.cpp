#include "cashregister.h"
#include <iomanip>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

CashRegister::CashRegister() : opState(INICIAR) {
  c001 = new Coin(0.01);
  c005 = new Coin(0.05);
  c010 = new Coin(0.10);
  c025 = new Coin(0.25);
  c050 = new Coin(0.50);
  c1 = new Coin(1);

  dataLoad();
}

void CashRegister::dataSave() {
  FILE *fp;
  char stateCoin[60];

  const char *filename = "dados.dat";
  const char *mode = "w+";
  fp = fopen(filename, mode);
  if (fp != NULL) {
    sprintf(stateCoin, "100: %d\n", this->getCountCoin(coin1));
    sprintf(&stateCoin[strlen(stateCoin)], "050: %d\n",
            this->getCountCoin(coin050));
    sprintf(&stateCoin[strlen(stateCoin)], "025: %d\n",
            this->getCountCoin(coin025));
    sprintf(&stateCoin[strlen(stateCoin)], "010: %d\n",
            this->getCountCoin(coin010));
    sprintf(&stateCoin[strlen(stateCoin)], "005: %d\n",
            this->getCountCoin(coin005));
    sprintf(&stateCoin[strlen(stateCoin)], "001: %d\n",
            this->getCountCoin(coin001));

    fwrite(stateCoin, strlen(stateCoin), 1, fp);
  }
  fclose(fp);
}

void CashRegister::dataLoad() {
  FILE *fp;
  const char *filename = "dados.dat";
  const char *mode = "r+";
  struct stat stFile;
  char *buff, *ptr;
  char coin[10];

  if (stat(filename, &stFile) == -1) {
    perror("stat");
    return;
  }
  buff = (char *)malloc(stFile.st_size);

  fp = fopen(filename, mode);
  if (fp != NULL) {
    fread(buff, stFile.st_size, 1, fp);
    ptr = strstr(buff, "100");
    loadCoin(ptr, coin);
    this->insertCoin(coin1, atoi(coin));
    loadCoin(ptr, coin);
    this->insertCoin(coin1, atoi(coin));
    ptr = strstr(buff, "050");
    loadCoin(ptr, coin);
    this->insertCoin(coin050, atoi(coin));
    ptr = strstr(buff, "025");
    loadCoin(ptr, coin);
    this->insertCoin(coin025, atoi(coin));
    ptr = strstr(buff, "010");
    loadCoin(ptr, coin);
    this->insertCoin(coin010, atoi(coin));
    ptr = strstr(buff, "005");
    loadCoin(ptr, coin);
    this->insertCoin(coin005, atoi(coin));
    ptr = strstr(buff, "001");
    loadCoin(ptr, coin);
    this->insertCoin(coin001, atoi(coin));
  }

  free(buff);
  fclose(fp);

  refreshBalance();
}

int CashRegister::getCountCoin(CashRegister::eCoinDef e) {
  int count = 0;

  switch (e) {
  case coin001:
    count = c001->getCount();
    break;
  case coin005:
    count = c005->getCount();
    break;
  case coin010:
    count = c010->getCount();
    break;
  case coin025:
    count = c025->getCount();
    break;
  case coin050:
    count = c050->getCount();
    break;
  case coin1:
    count = c1->getCount();
    break;
  }

  return count;
}

void CashRegister::insertCoin(CashRegister::eCoinDef e, int count) {
  switch (e) {
  case coin001:
    c001->setCount(count);
    break;
  case coin005:
    c005->setCount(count);
    break;
  case coin010:
    c010->setCount(count);
    break;
  case coin025:
    c025->setCount(count);
    break;
  case coin050:
    c050->setCount(count);
    break;
  case coin1:
    c1->setCount(count);
    break;
  }
}

void CashRegister::extractCoin(eCoinDef e, int count) {
  switch (e) {
  case coin001:
    if (c001->getCount() >= count) {
      c001->setCount(c001->getCount() - count);
    }
    break;
  case coin005:
    if (c005->getCount() >= count) {
      c005->setCount(c005->getCount() - count);
    }
    break;
  case coin010:
    if (c010->getCount() >= count) {
      c010->setCount(c010->getCount() - count);
    }
    break;
  case coin025:
    if (c025->getCount() >= count) {
      c025->setCount(c025->getCount() - count);
    }
    break;
  case coin050:
    if (c050->getCount() >= count) {
      c050->setCount(c050->getCount() - count);
    }
    break;
  case coin1:
    if (c1->getCount() >= count) {
      c1->setCount(c1->getCount() - count);
    }
    break;
  }
}

void CashRegister::refreshBalance() {
  balance = (c001->getValue() * (double)c001->getCount()) +
            (c005->getValue() * (double)c005->getCount()) +
            (c010->getValue() * (double)c010->getCount()) +
            (c025->getValue() * (double)c025->getCount()) +
            (c050->getValue() * (double)c050->getCount()) +
            (c1->getValue() * (double)c1->getCount());
}

void CashRegister::changeCalc(double change, int *coins1, int *coins050,
                              int *coins025, int *coins010, int *coins005,
                              int *coins001) {
  int count = 0;

  std::setprecision(2);

  count = c1->getCount();
  count -= (int)(change / 1);
  c1->setCount(count);
  if (coins1 != nullptr) {
    *coins1 = (int)(change / 1);
  }
  change -= ((int)(change / 1)) * 1;

  count = c050->getCount();
  count -= (int)(change / 0.50);
  c050->setCount(count);
  if (coins050 != nullptr) {
    *coins050 = (int)(change / 0.50);
  }
  change -= ((int)(change / 0.50)) * 0.50;

  count = c025->getCount();
  count -= (int)(change / 0.25);
  c025->setCount(count);
  if (coins025 != nullptr) {
    *coins025 = (int)(change / 0.25);
  }
  change -= ((int)(change / 0.25)) * 0.25;

  count = c010->getCount();
  count -= (int)(change / 0.10);
  c010->setCount(count);
  if (coins010 != nullptr) {
    *coins010 = (int)(change / 0.10);
  }
  change -= ((int)(change / 0.10)) * 0.10;

  count = c005->getCount();
  count -= (int)(change / 0.05);
  c005->setCount(count);
  if (coins005 != nullptr) {
    *coins005 = (int)(change / 0.10);
  }
  change -= ((int)(change / 0.05)) * 0.05;

  count = c001->getCount();
  count -= (int)(change / 0.01);
  printf("Change: %lf\n", change);
  printf("Resultado: %d\n", (int)(change / 0.01));
  printf("Resultado: %lf\n", (change / 0.01));
  c001->setCount(count);
  if (coins001 != nullptr) {
    *coins001 = (int)(change / 0.01);
  }
  change -= (((int)(change / 0.01)) * 0.01);
}

void CashRegister::loadCoin(char *ptr, char *coin) {
  if (ptr != NULL) {
      for (size_t i = 0; i < strlen(ptr); ++i) {
        if (ptr[i] == '\n') {
          coin[i] = 0;
          break;
        } else {
          coin[i] = ptr[5 + i];
        }
      }
  }
}
