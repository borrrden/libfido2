/*
 * Copyright (c) 2018 Yubico AB. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef _FIDO_H
#define _FIDO_H

#ifdef _FIDO_INTERNAL
#include <openssl/ec.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <cbor.h>

#include "blob.h"
#include "compat.h"
#include "es256.h"
#include "types.h"
#include "extern.h"
#endif

#include "fido/err.h"
#include "fido/param.h"

#ifndef _FIDO_INTERNAL
typedef struct fido_assert fido_assert_t;
typedef struct fido_cbor_info fido_cbor_info_t;
typedef struct fido_cred fido_cred_t;
typedef struct fido_dev fido_dev_t;
typedef struct fido_dev_info fido_dev_info_t;
typedef struct es256_pk es256_pk_t;
typedef struct es256_sk es256_sk_t;
#endif

es256_pk_t *es256_pk_new(void);
es256_sk_t *es256_sk_new(void);
fido_assert_t *fido_assert_new(void);
fido_cred_t *fido_cred_new(void);
fido_dev_t *fido_dev_new(void);
fido_dev_info_t *fido_dev_info_new(size_t);
fido_cbor_info_t *fido_cbor_info_new(void);

EVP_PKEY *es256_pk_to_EVP_PKEY(const es256_pk_t *);
EVP_PKEY *es256_sk_to_EVP_PKEY(const es256_sk_t *);

void es256_pk_free(es256_pk_t **);
void es256_sk_free(es256_sk_t **);
void fido_assert_free(fido_assert_t **);
void fido_cbor_info_free(fido_cbor_info_t **);
void fido_cred_free(fido_cred_t **);
void fido_dev_force_u2f(fido_dev_t *);
void fido_dev_free(fido_dev_t **);
void fido_dev_info_free(fido_dev_info_t **, size_t);
void fido_init(void);

const unsigned char *es256_pk_get_x(const es256_pk_t *);
const unsigned char *es256_pk_get_y(const es256_pk_t *);
const unsigned char *es256_sk_get_d(const es256_sk_t *);
const unsigned char *fido_assert_authdata_ptr(const fido_assert_t *, size_t);
const unsigned char *fido_assert_clientdata_hash_ptr(const fido_assert_t *);
const unsigned char *fido_assert_id_ptr(const fido_assert_t *, size_t);
const unsigned char *fido_assert_sig_ptr(const fido_assert_t *, size_t);
const unsigned char *fido_assert_user_id_ptr(const fido_assert_t *, size_t);

const char *fido_assert_user_display_name(const fido_assert_t *, size_t);
const char *fido_assert_user_icon(const fido_assert_t *, size_t);
const char *fido_assert_user_name(const fido_assert_t *, size_t);
const char *fido_cred_fmt(const fido_cred_t *);
const char *fido_dev_info_path(const fido_dev_info_t *);
const wchar_t *fido_dev_info_manufacturer_string(const fido_dev_info_t *);
const wchar_t *fido_dev_info_product_string(const fido_dev_info_t *);
const es256_pk_t *fido_cred_pubkey(const fido_cred_t *);
const unsigned char *fido_cred_authdata_ptr(const fido_cred_t *);
const unsigned char *fido_cred_clientdata_hash_ptr(const fido_cred_t *);
const unsigned char *fido_cred_id_ptr(const fido_cred_t *);
const unsigned char *fido_cred_sig_ptr(const fido_cred_t *);
const unsigned char *fido_cred_x5c_ptr(const fido_cred_t *);
const unsigned char *fido_cbor_info_aaguid_ptr(const fido_cbor_info_t *);
const uint8_t *fido_cbor_info_protocols_ptr(const fido_cbor_info_t *);
const bool *fido_cbor_info_options_value_ptr(const fido_cbor_info_t *);
const fido_dev_info_t *fido_dev_info_ptr(const fido_dev_info_t *, size_t);
char **fido_cbor_info_extensions_ptr(const fido_cbor_info_t *);
char **fido_cbor_info_options_name_ptr(const fido_cbor_info_t *);
char **fido_cbor_info_versions_ptr(const fido_cbor_info_t *);

int es256_derive_pk(const es256_sk_t *, es256_pk_t *);
int es256_pk_from_EC_KEY(const EC_KEY *, es256_pk_t *);
int es256_pk_set_x(es256_pk_t *, const unsigned char *);
int es256_pk_set_y(es256_pk_t *, const unsigned char *);
int es256_sk_create(es256_sk_t *);
int es256_sk_set_d(es256_sk_t *, const unsigned char *);
int fido_assert_allow_cred(fido_assert_t *, const unsigned char *, size_t);
int fido_assert_set_authdata(fido_assert_t *, size_t, const unsigned char *,
    size_t);
int fido_assert_set_clientdata_hash(fido_assert_t *, const unsigned char *,
    size_t);
int fido_assert_set_count(fido_assert_t *, size_t);
int fido_assert_set_options(fido_assert_t *, bool, bool);
int fido_assert_set_rp(fido_assert_t *, const char *);
int fido_assert_set_sig(fido_assert_t *, size_t, const unsigned char *, size_t);
int fido_assert_verify(fido_assert_t *, size_t, const es256_pk_t *);
int fido_cred_exclude(fido_cred_t *, const unsigned char *, size_t);
int fido_cred_set_authdata(fido_cred_t *, const unsigned char *, size_t);
int fido_cred_set_clientdata_hash(fido_cred_t *, const unsigned char *, size_t);
int fido_cred_set_fmt(fido_cred_t *, const char *);
int fido_cred_set_options(fido_cred_t *, bool, bool);
int fido_cred_set_rp(fido_cred_t *, const char *, const char *);
int fido_cred_set_sig(fido_cred_t *, const unsigned char *, size_t);
int fido_cred_set_user(fido_cred_t *, const unsigned char *, size_t,
    const char *, const char *, const char *);
int fido_cred_set_x509(fido_cred_t *, const unsigned char *, size_t);
int fido_cred_verify(const fido_cred_t *);
int fido_dev_close(fido_dev_t *);
int fido_dev_get_assert(fido_dev_t *, fido_assert_t *);
int fido_dev_get_cbor_info(fido_dev_t *, fido_cbor_info_t *);
int fido_dev_get_retry_count(fido_dev_t *, int *);
int fido_dev_info_manifest(fido_dev_info_t *, size_t, size_t *);
int fido_dev_make_cred(fido_dev_t *, fido_cred_t *, const char *);
int fido_dev_open(fido_dev_t *, const char *);
int fido_dev_reset(fido_dev_t *);
int fido_dev_set_pin(fido_dev_t *, const char *, const char *);

size_t fido_assert_authdata_len(const fido_assert_t *, size_t);
size_t fido_assert_clientdata_hash_len(const fido_assert_t *);
size_t fido_assert_count(const fido_assert_t *);
size_t fido_assert_id_len(const fido_assert_t *, size_t);
size_t fido_assert_sig_len(const fido_assert_t *, size_t);
size_t fido_assert_user_id_len(const fido_assert_t *, size_t);
size_t fido_cred_authdata_len(const fido_cred_t *);
size_t fido_cred_clientdata_hash_len(const fido_cred_t *);
size_t fido_cred_id_len(const fido_cred_t *);
size_t fido_cred_sig_len(const fido_cred_t *);
size_t fido_cred_x5c_len(const fido_cred_t *);
size_t fido_cbor_info_aaguid_len(const fido_cbor_info_t *);
size_t fido_cbor_info_extensions_len(const fido_cbor_info_t *);
size_t fido_cbor_info_options_len(const fido_cbor_info_t *);
size_t fido_cbor_info_protocols_len(const fido_cbor_info_t *);
size_t fido_cbor_info_versions_len(const fido_cbor_info_t *);

uint8_t  fido_assert_flags(const fido_assert_t *, size_t);
uint8_t  fido_cred_flags(const fido_cred_t *);
uint8_t  fido_dev_protocol(const fido_dev_t *);
uint8_t  fido_dev_major(const fido_dev_t *);
uint8_t  fido_dev_minor(const fido_dev_t *);
uint8_t  fido_dev_build(const fido_dev_t *);
uint8_t  fido_dev_flags(const fido_dev_t *);
int16_t  fido_dev_info_vendor(const fido_dev_info_t *);
int16_t  fido_dev_info_product(const fido_dev_info_t *);
uint64_t fido_cbor_info_maxmsgsiz(const fido_cbor_info_t *);

bool fido_dev_is_fido2(const fido_dev_t *);

#endif /* !_FIDO_H */