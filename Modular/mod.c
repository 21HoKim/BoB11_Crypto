#include <stdio.h>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM *a)
{
    char *number_str = BN_bn2dec(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}

int ExpMod(BIGNUM *r, const BIGNUM *a, const BIGNUM *e, BIGNUM *m)
{
    // a를e승 (mod m)한 결과
    BN_copy(r, a); //에 a의 값을 복사
    BN_CTX *ctx = BN_CTX_new();
    int i = BN_num_bits(e); // i는 e의 유효 비트수
    BIGNUM *p = BN_new();
    BN_dec2bn(&p, "2");
    for (i -= 2; i >= 0; i--)
    {
        BN_mod_exp(r, r, p, m, ctx);
        if (BN_is_bit_set(e, i) == 1)
        {
            BN_mod_mul(r, r, a, m, ctx);
        }
    }
}

int main(int argc, char *argv[])
{
    BIGNUM *a = BN_new();
    BIGNUM *e = BN_new();
    BIGNUM *m = BN_new();
    BIGNUM *res = BN_new();

    if (argc != 4)
    {
        printf("usage: exp base exponent modulus\n");
        return -1;
    }

    BN_dec2bn(&a, argv[1]);
    BN_dec2bn(&e, argv[2]);
    BN_dec2bn(&m, argv[3]);
    printBN("a = ", a);
    printBN("e = ", e);
    printBN("m = ", m);

    ExpMod(res, a, e, m);

    printBN("a**e mod m = ", res);

    if (a != NULL)
        BN_free(a);
    if (e != NULL)
        BN_free(e);
    if (m != NULL)
        BN_free(m);
    if (res != NULL)
        BN_free(res);

    return 0;
}