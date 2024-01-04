#include <stdio.h>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM * a)
{
        char * number_str = BN_bn2dec(a);
        printf("%s %s\n", msg, number_str);
        OPENSSL_free(number_str);
}

void ExpMod(BIGNUM *res, BIGNUM *a, BIGNUM *e, BIGNUM *m)
{
	// R2L
	BN_CTX *ctx = BN_CTX_new();
	
	BIGNUM *A = BN_new();
	BIGNUM *B = BN_new();
	
	BN_dec2bn(&A, "1");
	BN_copy(B, a);
	
	// q : quotient, r : remainder, t : 2
	BIGNUM *q = BN_new();
	BIGNUM *r = BN_new();
	BIGNUM *t = BN_new();
	
	BN_copy(q, e);
	BN_dec2bn(&t, "2");
	
	// no zero divide
	if(BN_is_zero(m))
		return;
	
	// a^0 = 1 = res
	if(BN_is_zero(e)){
		BN_dec2bn(&res, "1");
		return;
	}
	
	// else
	while(!BN_is_zero(q)){
		BN_div(q, r, q, t, ctx);
		
		if(BN_is_one(r)){
			BN_mod_mul(A, A, B, m, ctx);
		}
		BN_mod_mul(B, B, B, m, ctx);
	}
	
	if(ctx != NULL)
		BN_CTX_free(ctx);
	
	BN_copy(res, A);
	return;
}

int main (int argc, char *argv[])
{
        BIGNUM *a = BN_new();
        BIGNUM *e = BN_new();
        BIGNUM *m = BN_new();
        BIGNUM *res = BN_new();

        if(argc != 4){
                printf("usage: exp base exponent modulus\n");
                return -1;
        }

        BN_dec2bn(&a, argv[1]);
        BN_dec2bn(&e, argv[2]);
        BN_dec2bn(&m, argv[3]);
        printBN("a = ", a);
        printBN("e = ", e);
        printBN("m = ", m);

        ExpMod(res,a,e,m);

        printBN("a**e mod m = ", res);

        if(a != NULL) BN_free(a);
        if(e != NULL) BN_free(e);
        if(m != NULL) BN_free(m);
        if(res != NULL) BN_free(res);

        return 0;
}
