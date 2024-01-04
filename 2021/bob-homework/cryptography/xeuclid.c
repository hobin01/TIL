#include <stdio.h> 
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM *a)
{
	char *number_str = BN_bn2dec(a);
	printf("%s %s \n", msg, number_str);
	OPENSSL_free(number_str);
}

BIGNUM *XEuclid(BIGNUM *x, BIGNUM *y, const BIGNUM *a, const BIGNUM *b)
{
	BIGNUM *tmp1 = BN_new();
	BIGNUM *tmp2 = BN_new();
	BN_copy(tmp1, a);
	BN_copy(tmp2, b);

	BIGNUM *x1 = BN_new();
	BIGNUM *x2 = BN_new();
	BIGNUM *y1 = BN_new();
	BIGNUM *y2 = BN_new();
	BIGNUM *q  = BN_new();
	BIGNUM *r  = BN_new();
	BIGNUM *gcd = BN_new();
	
	BN_CTX *ctx = BN_CTX_new();
	
	BN_dec2bn(&x1, "1");
	BN_dec2bn(&x2, "0");
	BN_dec2bn(&y1, "0");
	BN_dec2bn(&y2, "1");
	
	BN_dec2bn(&r, "1");
	
	// exception 
	if(BN_is_zero(a) && BN_is_zero(b))
		goto err;
	
	// b = 0 인 경우 아래 알고리즘 에러
	if((BN_is_zero(a) && !BN_is_zero(b)) || (!BN_is_zero(a) && BN_is_zero(b))){
		if(!BN_is_zero(a) && BN_is_zero(b)){
			BN_dec2bn(&x, "1");
			BN_dec2bn(&y, "0");
			BN_copy(gcd, a);
			return gcd;
		}
	}
	
	// BN_div : 나누기 성공 = ret 0
	// q = a/b, r = a % b
	
	// extended euclid algorithm
	
	while(!BN_is_zero(r)){
		if(!BN_div(q, r, a, b, ctx))
			goto err;
		
		BN_mul(x, q, x2, ctx);
		BN_sub(x, x1, x);
		BN_mul(y, q, y2, ctx);
		BN_sub(y, y1, y);
		
		BN_copy(a, b);
		BN_copy(b, r);
		BN_copy(x1, x2);
		BN_copy(x2, x);
		BN_copy(y1, y2);
		BN_copy(y2, y);
	}
	
	BN_copy(gcd, a);
	BN_copy(x, x1);
	BN_copy(y, y1);
	
	BN_copy(a, tmp1);
	BN_copy(b, tmp2);
	
	// r is 0
	// BN_cmp(a, b) : a < b : -1, a == b : 0
	// case : gcd is negative
	if(BN_cmp(gcd, r) == -1){
		BIGNUM *minus_one = BN_new();
		BN_dec2bn(&minus_one, "-1");
		BN_mul(gcd, gcd, minus_one, ctx);
		BN_mul(x, x, minus_one, ctx);
		BN_mul(y, y, minus_one, ctx);
	}
	
	if(ctx != NULL)
		BN_CTX_free(ctx);
		
	return gcd;
	
err:
	return NULL;
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

