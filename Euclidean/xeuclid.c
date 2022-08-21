#include <stdio.h> 
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM * a){
  char * number_str = BN_bn2dec(a);
  printf("%s %s\n",msg,number_str);
  OPENSSL_free(number_str);
}
BIGNUM *XEuclid(BIGNUM *x, BIGNUM *y, const BIGNUM *a, const BIGNUM *b)
{
        BIGNUM *r1=BN_new();BN_copy(r1,a);
        BIGNUM *r2=BN_new();BN_copy(r2,b);
        BIGNUM *s1=BN_new();BN_dec2bn(&s1, "1");
        BIGNUM *s2=BN_new();BN_dec2bn(&s2, "0");
        BIGNUM *t1=BN_new();BN_dec2bn(&t1, "0");
        BIGNUM *t2=BN_new();BN_dec2bn(&t2, "1");
        BIGNUM *q=BN_new();
        BIGNUM *r=BN_new();
        BIGNUM *t=BN_new();
        BIGNUM *s=BN_new();
        BN_CTX *ctx=BN_CTX_new();
        BIGNUM *zero=BN_new();BN_zero(zero);
        BIGNUM *mul=BN_new();
if(BN_cmp(a,b)!=1){
        BN_swap(r1,r2);
}
        while(BN_cmp(r2,zero)==1){ //r2가 0보다 클때
                BN_div(q,r,r1,r2,ctx); // q=r1/r2, r=r1%r2;
                BN_copy(r1,r2);
                BN_copy(r2,r);
                
                BN_mul(mul,q,s2,ctx); //mul = q*s2
                BN_sub(s,s1,mul); //s=s1-q*s2
                BN_copy(s1,s2);
                BN_copy(s2,s);

                BN_mul(mul,q,t2,ctx); //mul = q*t2
                BN_sub(t,t1,mul); //t=t1-q*t2
                BN_copy(t1,t2);
                BN_copy(t2,t);
        
        }if(BN_cmp(a,b)!=1){
        BN_copy(y,s1);
        BN_copy(x,t1);
        }
        else{
        BN_copy(x,s1);
        BN_copy(y,t1);
        }
        return r1;

}

int main (int argc, char *argv[])
{
        BIGNUM *a = BN_new();
        BIGNUM *b = BN_new();
        BIGNUM *x = BN_new();
        BIGNUM *y = BN_new();
        BIGNUM *gcd;

        if(argc != 3){
                printf("usage: xeuclid num1 num2");
                return -1;
        }
        BN_dec2bn(&a, argv[1]);
        BN_dec2bn(&b, argv[2]);
        gcd = XEuclid(x,y,a,b);

        printBN("(a,b) = ", gcd);
        printBN("a = ", a);
        printBN("b = ", b);
        printBN("x = ", x);
        printBN("y = ", y);
        printf("%s*(%s) + %s*(%s) = %s\n",BN_bn2dec(a),BN_bn2dec(x),BN_bn2dec(b),BN_bn2dec(y),BN_bn2dec(gcd));

        if(a != NULL) BN_free(a);
        if(b != NULL) BN_free(b);
        if(x != NULL) BN_free(x);
        if(y != NULL) BN_free(y);
        if(gcd != NULL) BN_free(gcd);
        return 0;
}
