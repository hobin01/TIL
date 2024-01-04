#include <stdio.h>
#include <stdbool.h>
#include <openssl/bn.h>

/*
TODO : 
typedef struct _b10rsa_st
BOB10_RSA *BOB10_RSA_new();
int BOB10_RSA_free(BOB10_RSA *b10rsa);
int BOB10_RSA_KeyGen(BOB10_RSA *b10rsa, int nBits);
int BOB10_RSA_Enc(BIGNUM *c, BIGNUM *m, BOB10_RSA *b10rsa);
int BOB10_RSA_Dec(BIGNUM *m,BIGNUM *c, BOB10_RSA *b10rsa);

-----caution-------
input output : hex
modular inversion, exponetial : prev hw
libcrypto : only arithmetic operation and bits operation

using these primes
p=C485F491D12EA7E6FEB95794E9FE0A819168AAC9D545C9E2AE0C561622F265FEB965754C875E049B19F3F945F2574D57FA6A2FC0A0B99A2328F107DD16ADA2A7
q=F9A91C5F20FBBCCC4114FEBABFE9D6806A52AECDF5C9BAC9E72A07B0AE162B4540C62C52DF8A8181ABCC1A9E982DEB84DE500B27E902CD8FDED6B545C067CE4F
*/

typedef struct _b10rsa_st{
    BIGNUM *e;
    BIGNUM *d;
    BIGNUM *n;
}BOB10_RSA;

BOB10_RSA *BOB10_RSA_new()
{
    BOB10_RSA *b10rsa = (BOB10_RSA*)malloc(sizeof(BOB10_RSA));
    b10rsa->e = BN_new();
    b10rsa->d = BN_new();
    b10rsa->n = BN_new();

    return b10rsa;
}

int BOB10_RSA_free(BOB10_RSA *b10rsa)
{
    if(b10rsa->e != NULL)
        BN_free(b10rsa->e);
    if(b10rsa->d != NULL)
        BN_free(b10rsa->d);
    if(b10rsa->n != NULL)
        BN_free(b10rsa->n);

    return 1;
}

BIGNUM *GCD(BIGNUM *a, BIGNUM *b)
{
    // Get r = gcd(a, b) using euclidean algorithm
    BIGNUM *tmp;
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *r = BN_new();

    BIGNUM *A = BN_new();
    BIGNUM *B = BN_new();
    BN_copy(A, a);
    BN_copy(B, b);

    // A < B case
    if(BN_cmp(A, B) < 0){
        tmp = A;
        A = B;
        B = tmp;
    }

    while(!BN_is_zero(B)){
		if(!BN_mod(r, A, B, ctx)){
			goto err;
		}
		BN_copy(A, B);
		BN_copy(B, r);
	}

	BN_copy(r, A);

	if(ctx != NULL) BN_CTX_free(ctx);
    return r;

err:
	return NULL;

}

BIGNUM *Inverse_mod(BIGNUM *e, BIGNUM *mod_n)
{
    // inv = inverse of e on mod n
    // using extended euclidean algorithm
    BIGNUM *inv = BN_new();
    BIGNUM *q = BN_new();
    BIGNUM *r1 = BN_new();
    BIGNUM *r2 = BN_new();
    BIGNUM *r = BN_new();
    BIGNUM *s1 = BN_new();
    BIGNUM *s2 = BN_new();
    BIGNUM *s = BN_new();
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *tmp = BN_new(); // tmp = q * s2 
    BIGNUM *zero = BN_new();

    BN_zero(zero);

    // zero division error
    if(BN_is_zero(mod_n))
        goto err;

    BN_copy(r1, mod_n); // r1 = n 
    BN_mod(r2, e, mod_n, ctx); // r2 = e mod n
    BN_copy(r, mod_n); 
    BN_zero(s1);
    BN_one(s2);

    while(!BN_is_zero(r)){
        BN_div(q, r, r1, r2, ctx);
        BN_mul(tmp, q, s2, ctx);
        BN_sub(s, s1, tmp);
        BN_copy(r1, r2);
        BN_copy(r2, r);
        BN_copy(s1, s2);
        BN_copy(s2, s);
    }

    if(BN_is_one(r1)){
        BN_mod(s1, s1, mod_n, ctx);
        if(BN_cmp(s1, zero) == -1)
            BN_add(s1, s1, mod_n); // s1 : negative => positive (-s1 = n -s1 mod n)
        BN_copy(inv, s1);
    }
    else
        goto err; // inverse of e is none

    if(ctx != NULL) BN_CTX_free(ctx);
    if(q != NULL) BN_free(q);
    if(r1 != NULL) BN_free(r1);
    if(r2 != NULL) BN_free(r2);
    if(r != NULL) BN_free(r);
    if(s1 != NULL) BN_free(s1);
    if(s2 != NULL) BN_free(s2);
    if(s != NULL) BN_free(s);
    if(tmp != NULL) BN_free(tmp);
    if(zero != NULL) BN_free(zero);

    return inv;

err:
    return NULL;
}

void exp_modular(BIGNUM *result, BIGNUM *a, BIGNUM *e, BIGNUM *n)
{
    // result = a^e mod n
    BN_CTX *ctx = BN_CTX_new();

    BIGNUM *A = BN_new();

    BN_copy(A, a);
    int bit_len = BN_num_bits(e);

    for(int i = bit_len - 2; i >= 0; i--){
        BN_mul(A, A, A, ctx); 
        BN_mod(A, A, n, ctx); // A = A^2 mod n
        if(BN_is_bit_set(e, i)){
            BN_mul(A, A, a, ctx);
            BN_mod(A, A, n, ctx); // A = A * a  mod n
        }
    }

    BN_copy(result, A);
    
    if(ctx != NULL) BN_CTX_free(ctx);
    if(A != NULL) BN_free(A);

    return;
}

int BOB10_RSA_KeyGen(BOB10_RSA *b10rsa, int nBits)
{
    // p and q are primes
    BIGNUM *p = BN_new();
    BIGNUM *q = BN_new();

    BIGNUM *n = BN_new();
    BIGNUM *e = BN_new();
    BIGNUM *d = BN_new();

    BIGNUM *phi_n = BN_new();
    BN_CTX *ctx = BN_CTX_new();

    BIGNUM *one = BN_new();
    BIGNUM *phi_p = BN_new();
    BIGNUM *phi_q = BN_new();

    BIGNUM *phi_n_copy = BN_new();

    BN_one(one);
    BN_hex2bn(&p, "C485F491D12EA7E6FEB95794E9FE0A819168AAC9D545C9E2AE0C561622F265FEB965754C875E049B19F3F945F2574D57FA6A2FC0A0B99A2328F107DD16ADA2A7");
    BN_hex2bn(&q, "F9A91C5F20FBBCCC4114FEBABFE9D6806A52AECDF5C9BAC9E72A07B0AE162B4540C62C52DF8A8181ABCC1A9E982DEB84DE500B27E902CD8FDED6B545C067CE4F");

    // get integer e and d = inverse of e (mod phi(n))
    BN_mul(n, p, q, ctx); // n = p * q
    BN_sub(phi_p, p, one); // phi_p = p - 1 = phi(p)
    BN_sub(phi_q, q, one); // phi_q = q - 1 = phi(q)
    BN_mul(phi_n, phi_p, phi_q, ctx); // phi(n) = phi(p) * phi(q)

    BN_dec2bn(&e, "3"); // set initial e = 3 and find e s.t. gcd(e, phi(n)) = 1

    BN_copy(phi_n_copy, phi_n); // copy phi(n)
    
    // gcd == 1 => cmp return 0
    while(true){
        BIGNUM *gcd = GCD(phi_n, e);

        if(BN_is_one(gcd)){
            break;
        }

        BN_copy(phi_n, phi_n_copy);
        BN_add(e, e, one);
    }

    BN_copy(phi_n, phi_n_copy);

    d = Inverse_mod(e, phi_n);

    BN_copy(b10rsa->e, e);
    BN_copy(b10rsa->n, n);
    BN_copy(b10rsa->d, d);

    if(p != NULL) BN_free(p);
    if(q != NULL) BN_free(q);
    if(n != NULL) BN_free(n);
    if(e != NULL) BN_free(e);
    if(d != NULL) BN_free(d);
    if(phi_n != NULL) BN_free(phi_n);
    if(ctx != NULL) BN_CTX_free(ctx);
    if(one != NULL) BN_free(one);
    if(phi_p != NULL) BN_free(phi_p);
    if(phi_q != NULL) BN_free(phi_q);
    if(phi_n_copy != NULL) BN_free(phi_n_copy);

    return 1;
}

int BOB10_RSA_Enc(BIGNUM *c, BIGNUM *m, BOB10_RSA *b10rsa)
{
    exp_modular(c, m, b10rsa->e, b10rsa->n);

    return 1;
}

int BOB10_RSA_Dec(BIGNUM *m, BIGNUM *c, BOB10_RSA *b10rsa)
{
    exp_modular(m, c, b10rsa->d, b10rsa->n);

    return 1;
}

void PrintUsage()
{
    printf("usage: rsa [-k|-e e n plaintext|-d d n ciphertext]\n");
}

int main (int argc, char *argv[])
{
    BOB10_RSA *b10rsa = BOB10_RSA_new();
    BIGNUM *in = BN_new();
    BIGNUM *out = BN_new();

    if(argc == 2){
        if(strncmp(argv[1],"-k",2)){
            PrintUsage();
            return -1;
        }
        BOB10_RSA_KeyGen(b10rsa,1024);
        BN_print_fp(stdout,b10rsa->n);
        printf(" ");
        BN_print_fp(stdout,b10rsa->e);
        printf(" ");
        BN_print_fp(stdout,b10rsa->d);
    }
    else if(argc == 5){
        if(strncmp(argv[1],"-e",2) && strncmp(argv[1],"-d",2)){
            PrintUsage();
            return -1;
        }
        BN_hex2bn(&b10rsa->n, argv[3]);
        BN_hex2bn(&in, argv[4]);
        if(!strncmp(argv[1],"-e",2)){
            BN_hex2bn(&b10rsa->e, argv[2]);
            BOB10_RSA_Enc(out,in, b10rsa);
        }
        else if(!strncmp(argv[1],"-d",2)){
            BN_hex2bn(&b10rsa->d, argv[2]);
            BOB10_RSA_Dec(out,in, b10rsa);
        }
        else{
            PrintUsage();
            return -1;
        }
        BN_print_fp(stdout,out);
    }
    else{
        PrintUsage();
        return -1;
    }

    if(in != NULL) BN_free(in);
    if(out != NULL) BN_free(out);
    if(b10rsa!= NULL) BOB10_RSA_free(b10rsa);

    return 0;
}
