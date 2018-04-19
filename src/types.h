/*
 * Copyright (c) 2018 Yubico AB. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef _TYPES_H
#define _TYPES_H

typedef struct fido_authdata {
	unsigned char rp_id_hash[32]; /* sha256 of fido_rp.id */
	uint8_t       flags;          /* user present/verified */
	uint32_t      sigcount;       /* signature counter */
	/* actually longer */
} __attribute__ ((packed)) fido_authdata_t;

typedef struct fido_attcred {
	unsigned char aaguid[16]; /* credential's aaguid */
	fido_blob_t   id;         /* credential id */
	es256_pk_t    pubkey;     /* credential's public key */
} fido_attcred_t;

typedef struct fido_attstmt {
	fido_blob_t x5c; /* attestation certificate */
	fido_blob_t sig; /* attestation signature */
} fido_attstmt_t;

typedef struct fido_rp {
	char *id;   /* relying party id */
	char *name; /* relying party name */
} fido_rp_t;

typedef struct fido_user {
	fido_blob_t  id;           /* required */
	char        *icon;         /* optional */
	char        *name;         /* optional */
	char        *display_name; /* required */
} fido_user_t;

typedef struct fido_cred {
	fido_blob_t       cdh;           /* client data hash */
	fido_rp_t         rp;            /* relying party */
	fido_user_t       user;          /* user entity */
	fido_blob_array_t excl;          /* list of credential ids to exclude */
	bool              rk;            /* resident key */
	bool              uv;            /* user verification */
	char             *fmt;           /* credential format */
	fido_blob_t       authdata_cbor; /* raw cbor payload */
	fido_authdata_t   authdata;      /* decoded authdata payload */
	fido_attcred_t    attcred;       /* returned credential (key + id) */
	fido_attstmt_t    attstmt;       /* attestation statement (x509 + sig) */
} fido_cred_t;

typedef struct _fido_assert_stmt {
	fido_blob_t     id;            /* credential id */
	fido_user_t     user;          /* user attributes */
	fido_blob_t     authdata_cbor; /* raw cbor payload */
	fido_authdata_t authdata;      /* decoded authdata payload */
	fido_blob_t     sig;           /* signature of cdh + authdata */
} fido_assert_stmt;

typedef struct fido_assert {
	char              *rp_id;        /* relying party id */
	fido_blob_t        cdh;          /* client data hash */
	fido_blob_array_t  allow_list;   /* list of allowed credentials */
	bool               up;           /* user presence */
	bool               uv;           /* user verification */
	fido_assert_stmt  *stmt;         /* array of expected assertions */
	size_t             stmt_cnt;     /* number of allocated assertions */
        size_t             stmt_len;     /* number of received assertions */
} fido_assert_t;

typedef struct fido_opt_array {
	char **name;
	bool *value;
	size_t len;
} fido_opt_array_t;

typedef struct fido_str_array {
	char **ptr;
	size_t len;
} fido_str_array_t;

typedef struct fido_byte_array {
	uint8_t *ptr;
	size_t len;
} fido_byte_array_t;

typedef struct fido_cbor_info {
	fido_str_array_t  versions;   /* supported versions: fido2|u2f */
	fido_str_array_t  extensions; /* list of supported extensions */
	unsigned char     aaguid[16]; /* aaguid */
	fido_opt_array_t  options;    /* list of supported options */
	uint64_t          maxmsgsiz;  /* maximum message size */
	fido_byte_array_t protocols;  /* supported pin protocols */
} fido_cbor_info_t;

#include <hidapi.h>

typedef struct fido_dev_info {
	char    *path;         /* device path */
	int16_t  vendor_id;    /* 2-byte vendor id */
	int16_t  product_id;   /* 2-byte product id */
	wchar_t *manufacturer; /* manufacturer string */
	wchar_t *product;      /* product string */
} fido_dev_info_t;

/* defined in section 8.1.9.1.3 (CTAPHID_INIT) of the fido2 ctap spec */
typedef struct fido_ctap_info {
	uint64_t nonce;    /* echoed nonce */
	uint32_t cid;      /* channel id */
	uint8_t  protocol; /* ctaphid protocol id */
	uint8_t  major;    /* major version number */
	uint8_t  minor;    /* minor version number */
	uint8_t  build;    /* build version number */
	uint8_t  flags;    /* capabilities flags; see FIDO_CAP_* */
} __attribute__ ((packed)) fido_ctap_info_t;

typedef struct fido_dev {
	uint64_t          nonce; /* issued nonce */
	fido_ctap_info_t  attr;  /* device attributes */
	hid_device       *hid;   /* underlying hid handle */
	uint32_t          cid;   /* assigned channel id */
} fido_dev_t;

#endif /* !_TYPES_H */