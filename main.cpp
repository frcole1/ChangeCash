#include "cashregister.h"
#include <iostream>

using namespace std;

int main() {
  int state = 0;
  int coinSelect = 0;
  int coinCount = 0;
  double coinChange = 0;
  CashRegister cashreg;

  cashreg.refreshBalance();

  while (1) {
    switch (cashreg.getOpState()) {

    case CashRegister::INICIAR:
      printf("\n\nSeu saldo Atual: R$%.2f", cashreg.getBalance());
      printf("\n\nESCOLHA A OPCAO:\n\n");
      printf("1 - Sair\n");
      printf("2 - Depositar Moeda\n");
      printf("3 - Sangrar Moeda\n");
      printf("4 - Valor Troco\n");
      scanf("%d", &state);
      if ((state > 0) && (state < 5)) {
          printf("OPCAO: %d\n", state);
          cashreg.setOpState(state);
      } else {
        printf("OPCAO: Invalida!!!\n");
        //printf("Press any key to continue...");
        //fflush(stdin);
        //getchar();
      }
      //cashreg.setOpState(state);
      break;

    case CashRegister::SAIR:
      printf("\n\nFINALIZADA OPERAÇÂO !!!\n\n");
      //printf("Press any key to continue...");
      fflush(stdin);
      getchar();
      exit(0);
      break;

    case CashRegister::DEPOSITAR:
      //system("clear");
      printf("\n\nDEPOSITE A MOEDA\n\n");
      // TODO :printf("0 : R$: 0.01 %d\n",
      // cashreg.getCountCoin((CashRegister::eCoinDef)0));
      printf("0 : R$: 0.01 Moeda(s): %d\n", cashreg.getCountCoin((CashRegister::eCoinDef)0));
      printf("1 : R$: 0.05 Moeda(s): %d\n", cashreg.getCountCoin((CashRegister::eCoinDef)1));
      printf("2 : R$: 0.10 Moeda(s): %d\n", cashreg.getCountCoin((CashRegister::eCoinDef)2));
      printf("3 : R$: 0.25 Moeda(s): %d\n", cashreg.getCountCoin((CashRegister::eCoinDef)3));
      printf("4 : R$: 0.50 Moeda(s): %d\n", cashreg.getCountCoin((CashRegister::eCoinDef)4));
      printf("5 : R$: 1.00 Moeda(s): %d\n", cashreg.getCountCoin((CashRegister::eCoinDef)5));
      scanf("%d", &coinSelect);
      if(coinSelect <= 5) {
          printf("OPCAO: %d\n", coinSelect);
          cashreg.setOpState(CashRegister::QUANTIDADE);
      } else
          printf("OPCAO: Invalida!!!\n");

      //printf("Press any key to continue...");
      //fflush(stdin);
      //getchar();
      /*
      printf("OPCAO: %d\n", coinSelect);
      printf("Press any key to continue...");
      fflush(stdin);
      getchar();
      cashreg.setOpState(CashRegister::QUANTIDADE);
      */
      break;

    case CashRegister::TROCAR: {
      int count1 = 0;
      int count050 = 0;
      int count025 = 0;
      int count010 = 0;
      int count005 = 0;
      int count001 = 0;

      system("clear");
      printf("\n\nVALOR DE TROCO\n\n");
      scanf("%lf", &coinChange);
      if (cashreg.getBalance() >= coinChange) {

        cashreg.changeCalc(coinChange, &count1, &count050, &count025, &count010,
                           &count005, &count001);
        //        std::cout << "Moedas de de 1,00: "<< count1 << std::endl;
        printf("\n\nMOEDA(S) PARA TROCO:\n\n");
        printf("Moeda(s) de de 1,00: %d\n", count1);
        printf("Moeda(s) de de 0,50: %d\n", count050);
        printf("Moeda(s) de de 0,25: %d\n", count025);
        printf("Moeda(s) de de 0,10: %d\n", count010);
        printf("Moeda(s) de de 0,05: %d\n", count005);
        printf("Moeda(s) de de 0,01: %d\n\n", count001);
        //printf("Press any key to continue...");
        cashreg.refreshBalance();
        cashreg.dataSave();
        //fflush(stdin);
        //getchar();
        cashreg.setOpState(CashRegister::INICIAR);

      } else
        cashreg.setOpState(CashRegister::INSUFICIENTE);
    } break;

    case CashRegister::QUANTIDADE:
      // system("clear");
      printf("\n\nQUANTIDADE DESTA MOEDA\n\n");
      scanf("%d", &coinCount);
      //printf("Press any key to continue...");
      //fflush(stdin);
      //getchar();
      cashreg.setOpState(CashRegister::ATUALIZAR);
      break;

    case CashRegister::ATUALIZAR:
      cashreg.insertCoin((CashRegister::eCoinDef)coinSelect, coinCount);
      cashreg.refreshBalance();
      cashreg.dataSave();
      cashreg.setOpState(CashRegister::INICIAR);
      break;

    case CashRegister::INSUFICIENTE:
      printf("\n\nSALDO INSUFICIENTE!!!\n\n");
      printf("Press any key to continue...");
      fflush(stdin);
      getchar();
      cashreg.setOpState(CashRegister::INICIAR);
      break;

    case CashRegister::SANGRAR:
      system("clear");
      printf("\n\nSANGRAR A MOEDA\n\n");
      printf("0 : R$: 0.01 Moeda(s): %d\n", cashreg.getCountCoin((CashRegister::eCoinDef)0));
      printf("1 : R$: 0.05 Moeda(s): %d\n", cashreg.getCountCoin((CashRegister::eCoinDef)1));
      printf("2 : R$: 0.10 Moeda(s): %d\n", cashreg.getCountCoin((CashRegister::eCoinDef)2));
      printf("3 : R$: 0.25 Moeda(s): %d\n", cashreg.getCountCoin((CashRegister::eCoinDef)3));
      printf("4 : R$: 0.50 Moeda(s): %d\n", cashreg.getCountCoin((CashRegister::eCoinDef)4));
      printf("5 : R$: 1.00 Moeda(s): %d\n", cashreg.getCountCoin((CashRegister::eCoinDef)5));
      scanf("%d", &coinSelect);

      if(coinSelect <= 5) {
          printf("OPCAO: %d\n", coinSelect);
          cashreg.setOpState(CashRegister::QUANTSANGRAR);
      } else
          printf("OPCAO: Invalida!!!\n");

      printf("Press any key to continue...");
      fflush(stdin);
      getchar();
      break;

    case CashRegister::QUANTSANGRAR:
      // system("clear");
      printf("\n\nQUANTIDADE DESTA MOEDA\n\n");
      scanf("%d", &coinCount);

      if (cashreg.getCountCoin((CashRegister::eCoinDef)coinSelect) >=
          coinCount) {
        printf("Press any key to continue...");
        fflush(stdin);
        getchar();
        cashreg.setOpState(CashRegister::ATUSANGRAR);
      } else
        cashreg.setOpState(CashRegister::INSUFICIENTE);
      break;

    case CashRegister::ATUSANGRAR:
      cashreg.extractCoin((CashRegister::eCoinDef)coinSelect, coinCount);
      cashreg.refreshBalance();
      cashreg.dataSave();
      cashreg.setOpState(CashRegister::INICIAR);
      break;
    }
  }
  return 0;
}
