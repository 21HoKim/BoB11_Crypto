#include<stdio.h>
#include<openssl/bn.h>



void printBN(char *msg, BIGNUM * a){
  char * number_str = BN_bn2hex(a);
  printf("%s %s\n",msg,number_str);
  OPENSSL_free(number_str);



}

int main(){
  BN_CTX *ctx = BN_CTX_new();
  BIGNUM *a = BN_new();
  BIGNUM *b = BN_new();
  BIGNUM *res = BN_new();

  BN_dec2bn(&a, "111");
  BN_dec2bn(&b,"222");
  printBN("a = ",a);
  printBN("b = ",b);
  BN_mul(res,a,b,ctx);
  printBN("a*b = ",res);
  BN_add(res,a,b);
  printBN("a+b = ",res);
  return 0;
}
/*
-----start-----
a =  6F
b =  DE
a*b =  6042
a+b =  014D
---------------
*/