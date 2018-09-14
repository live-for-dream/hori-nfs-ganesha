/*
 * Copyright (C) 2014 CohortFS, LLC.
 * Author: William Allen Simpson <bill@CohortFS.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

/**
 * @defgroup NFS compound data
 * @{
 */

/**
 * @file   nfs_proto_data.h
 * @author William Allen Simpson <bill@CohortFS.com>
 * @date   Wed Nov 19 14:11:19 2014
 *
 * @brief NFS compound data, function arguments, and return status
 *
 * @note called only from sal_data.h
 */

#ifndef NFS_PROTO_DATA_H
#define NFS_PROTO_DATA_H

#include "fsal_api.h"
#include "rquota.h"

/*
 * mount was autogenerated, and requires several headers to compile;
 * rather than scattered through the code, consolidated in nfs23.h.
 * (Used by the mass compound unions here.)
 */
#include "nfs23.h"
#include "nfs4.h"
#include "nlm4.h"

/* ------------------------------ Typedefs and structs----------------------- */

typedef union nfs_arg__ {
	GETATTR3args arg_getattr3;
	SETATTR3args arg_setattr3;
	LOOKUP3args arg_lookup3;
	ACCESS3args arg_access3;
	READLINK3args arg_readlink3;
	READ3args arg_read3;
	WRITE3args arg_write3;
	CREATE3args arg_create3;
	MKDIR3args arg_mkdir3;
	SYMLINK3args arg_symlink3;
	MKNOD3args arg_mknod3;
	REMOVE3args arg_remove3;
	RMDIR3args arg_rmdir3;
	RENAME3args arg_rename3;
	LINK3args arg_link3;
	READDIR3args arg_readdir3;
	READDIRPLUS3args arg_readdirplus3;
	FSSTAT3args arg_fsstat3;
	FSINFO3args arg_fsinfo3;
	PATHCONF3args arg_pathconf3;
	COMMIT3args arg_commit3;
	COMPOUND4args arg_compound4;

	/* mnt */
	dirpath arg_mnt;

	/* nlm */
	nlm4_testargs arg_nlm4_test;
	nlm4_lockargs arg_nlm4_lock;
	nlm4_cancargs arg_nlm4_cancel;
	nlm4_shareargs arg_nlm4_share;
	nlm4_unlockargs arg_nlm4_unlock;
	nlm4_sm_notifyargs arg_nlm4_sm_notify;
	nlm4_free_allargs arg_nlm4_free_allargs;
	nlm4_res arg_nlm4_res;

	/* Rquota */
	getquota_args arg_rquota_getquota;
	getquota_args arg_rquota_getactivequota;
	setquota_args arg_rquota_setquota;
	setquota_args arg_rquota_setactivequota;

	/* Ext Rquota */
	ext_getquota_args arg_ext_rquota_getquota;
	ext_getquota_args arg_ext_rquota_getactivequota;
	ext_setquota_args arg_ext_rquota_setquota;
	ext_setquota_args arg_ext_rquota_setactivequota;
} nfs_arg_t;

struct COMPOUND4res_extended {
	COMPOUND4res res_compound4;
	bool res_cached;
};

typedef union nfs_res__ {
	GETATTR3res res_getattr3;
	SETATTR3res res_setattr3;
	LOOKUP3res res_lookup3;
	ACCESS3res res_access3;
	READLINK3res res_readlink3;
	READ3res res_read3;
	WRITE3res res_write3;
	CREATE3res res_create3;
	MKDIR3res res_mkdir3;
	SYMLINK3res res_symlink3;
	MKNOD3res res_mknod3;
	REMOVE3res res_remove3;
	RMDIR3res res_rmdir3;
	RENAME3res res_rename3;
	LINK3res res_link3;
	READDIR3res res_readdir3;
	READDIRPLUS3res res_readdirplus3;
	FSSTAT3res res_fsstat3;
	FSINFO3res res_fsinfo3;
	PATHCONF3res res_pathconf3;
	COMMIT3res res_commit3;
	COMPOUND4res res_compound4;
	struct COMPOUND4res_extended res_compound4_extended;

	/* mount */
	fhstatus2 res_mnt1;
	exports res_mntexport;
	mountres3 res_mnt3;
	mountlist res_dump;

	/* nlm4 */
	nlm4_testres res_nlm4test;
	nlm4_res res_nlm4;
	nlm4_shareres res_nlm4share;

	/* Rquota */
	getquota_rslt res_rquota_getquota;
	getquota_rslt res_rquota_getactivequota;
	setquota_rslt res_rquota_setquota;
	setquota_rslt res_rquota_setactivequota;

	/* Ext Rquota */
	getquota_rslt res_ext_rquota_getquota;
	getquota_rslt res_ext_rquota_getactivequota;
	setquota_rslt res_ext_rquota_setquota;
	setquota_rslt res_ext_rquota_setactivequota;
} nfs_res_t;

/* flags related to the behaviour of the requests
 * (to be stored in the dispatch behaviour field)
 */
#define NOTHING_SPECIAL 0x0000	/* Nothing to be done for this kind of
				   request */
#define MAKES_WRITE	0x0001	/* The function modifyes the FSAL
				   (not permitted for RO FS) */
#define NEEDS_CRED	0x0002	/* A credential is needed for this
				   operation */
#define CAN_BE_DUP	0x0004	/* Handling of dup request can be done
				   for this request */
#define SUPPORTS_GSS	0x0008	/* Request may be authenticated by
				   RPCSEC_GSS */
#define MAKES_IO	0x0010	/* Request may do I/O
				   (not allowed on MD ONLY exports */

typedef int (*nfs_protocol_function_t) (nfs_arg_t *,
					struct svc_req *,
					nfs_res_t *);

typedef int (*nfsremote_protocol_function_t) (CLIENT *, nfs_arg_t *,
					      nfs_res_t *);

typedef void (*nfs_protocol_free_t) (nfs_res_t *);

typedef struct nfs_function_desc__ {
	nfs_protocol_function_t service_function;
	nfs_protocol_free_t free_function;
	xdrproc_t xdr_decode_func;
	xdrproc_t xdr_encode_func;
	char *funcname;
	unsigned int dispatch_behaviour;
} nfs_function_desc_t;

typedef struct nfs_request {
	struct svc_req svc;
	struct nfs_request_lookahead lookahead;
	nfs_arg_t arg_nfs;
	nfs_res_t *res_nfs;
	const nfs_function_desc_t *funcdesc;
} nfs_request_t;

enum rpc_chan_type {
	RPC_CHAN_V40,
	RPC_CHAN_V41
};

typedef struct rpc_call_channel {
	enum rpc_chan_type type;
	pthread_mutex_t mtx;
	uint32_t states;
	union {
		nfs_client_id_t *clientid;
		nfs41_session_t *session;
	} source;
	time_t last_called;
	CLIENT *clnt;
	AUTH *auth;
#ifdef _HAVE_GSSAPI
	struct rpc_gss_sec gss_sec;
#endif /* _HAVE_GSSAPI */
} rpc_call_channel_t;

/**
 * @todo Matt: this is automatically redundant, but in fact upstream
 * TI-RPC is not up-to-date with RFC 5665, will fix (Matt)
 *
 * @copyright 2012-2017, Linux Box Corp
*/
enum rfc_5665_nc_type {
	_NC_ERR,
	_NC_TCP,
	_NC_TCP6,
	_NC_RDMA,
	_NC_RDMA6,
	_NC_SCTP,
	_NC_SCTP6,
	_NC_UDP,
	_NC_UDP6,
};
typedef enum rfc_5665_nc_type nc_type;

struct __netid_nc_table {
	const char *netid;
	int netid_len;
	/* nc_type */
	const nc_type nc;
	int af;
};

extern const struct __netid_nc_table netid_nc_table[9];

nc_type nfs_netid_to_nc(const char *netid);
void nfs_set_client_location(nfs_client_id_t *pclientid,
			     const clientaddr4 *addr4);

/* end TI-RPC */

typedef struct gsh_addr {
	nc_type nc;
	struct sockaddr_storage ss;
	uint32_t port;
} gsh_addr_t;

/* NFS4 specific structures */

typedef struct nfs_client_cred_gss {
	unsigned int svc;
	unsigned int qop;
#ifdef _HAVE_GSSAPI
	struct svc_rpc_gss_data *gd;
#endif
} nfs_client_cred_gss_t;

typedef struct nfs_client_cred__ {
	unsigned int flavor;
	unsigned int length;
	union {
		struct authunix_parms auth_unix;
		nfs_client_cred_gss_t auth_gss;
	} auth_union;
} nfs_client_cred_t;

/**
 * @brief NFS v4 Compound Data
 *
 * This structure contains the necessary stuff for keeping the state
 * of a V4 compound request.
 */

/**
 * @brief Compound data
 *
 * This structure contains the necessary stuff for keeping the state
 * of a V4 compound request.
 */
typedef struct compound_data {
	nfs_fh4 currentFH;	/*< Current filehandle */
	nfs_fh4 savedFH;	/*< Saved filehandle */
	stateid4 current_stateid;	/*< Current stateid */
	bool current_stateid_valid;	/*< Current stateid is valid */
	stateid4 saved_stateid;	/*< Saved stateid */
	bool saved_stateid_valid;	/*< Saved stateid is valid */
	unsigned int minorversion;	/*< NFSv4 minor version */
	struct fsal_obj_handle *current_obj;	/*< Current object handle */
	struct fsal_obj_handle *saved_obj;	/*< saved object handle */
	struct fsal_ds_handle *current_ds;	/*< current ds handle */
	struct fsal_ds_handle *saved_ds;	/*< Saved DS handle */
	object_file_type_t current_filetype;    /*< File type of current obj */
	object_file_type_t saved_filetype;	/*< File type of saved entry */
	struct gsh_export *saved_export; /*< Export entry related to the
					     savedFH */
	struct export_perms saved_export_perms; /*< Permissions for export for
					       savedFH */
	struct svc_req *req;	/*< RPC Request related to the compound */
	nfs_client_cred_t credential;	/*< Raw RPC credentials */
	nfs_client_id_t *preserved_clientid;	/*< clientid that has lease
						   reserved, if any */
	struct COMPOUND4res_extended *cached_res;	/*< NFv41: pointer to
							   cached RPC result in
							   a session's slot */
	bool use_drc;		/*< Set to true if session DRC is to be used */
	uint32_t oppos;		/*< Position of the operation within the
				    request processed  */
	nfs41_session_t *session;	/*< Related session
					   (found by OP_SEQUENCE) */
	sequenceid4 sequence;	/*< Sequence ID of the current compound
				   (if applicable) */
	slotid4 slot;		/*< Slot ID of the current compound
				   (if applicable) */
} compound_data_t;

typedef int (*nfs4_op_function_t) (struct nfs_argop4 *, compound_data_t *,
				   struct nfs_resop4 *);

/**
 * @brief Set the current entry in the context
 *
 * This manages refcounting on the object being stored in data.  This means it
 * takes a ref on a new object, and releases it's ref on any old object.  If the
 * caller has it's own ref, it must release it itself.
 *
 * @param[in] data	Compound data to set entry in
 * @param[in] obj	Object to set
 */
static inline void set_current_entry(compound_data_t *data,
				     struct fsal_obj_handle *obj)
{
	/* Mark current_stateid as invalid */
	data->current_stateid_valid = false;

	/* Clear out the current_ds */
	if (data->current_ds) {
		ds_handle_put(data->current_ds);
		data->current_ds = NULL;
	}

	if (data->current_obj) {
		/* Release ref on old object */
		data->current_obj->obj_ops.put_ref(data->current_obj);
	}

	data->current_obj = obj;

	if (obj == NULL) {
		data->current_filetype = NO_FILE_TYPE;
		return;
	}

	/* Get our ref on the new object */
	data->current_obj->obj_ops.get_ref(data->current_obj);

	/* Set the current file type */
	data->current_filetype = obj->type;
}

/**
 * @brief Set the saved entry in the context
 *
 * This manages refcounting on the object being stored in data.  This means it
 * takes a ref on a new object, and releases it's ref on any old object.  If the
 * caller has it's own ref, it must release it itself.
 *
 * @param[in] data	Compound data to set entry in
 * @param[in] obj	Object to set
 */
static inline void set_saved_entry(compound_data_t *data,
				   struct fsal_obj_handle *obj)
{
	struct gsh_export *current_export = op_ctx->ctx_export;
	struct export_perms current_export_perms = *op_ctx->export_perms;
	bool restore_op_ctx = false;

	if (data->saved_ds != NULL || data->saved_obj != NULL) {
		/* Setup correct op_ctx for releasing old saved */
		op_ctx->ctx_export = data->saved_export;
		op_ctx->fsal_export = data->saved_export
					? data->saved_export->fsal_export
					: NULL;
		*op_ctx->export_perms = data->saved_export_perms;
		restore_op_ctx = true;
	}

	/* Mark saved_stateid as invalid */
	data->saved_stateid_valid = false;

	/* Clear out the saved_ds */
	if (data->saved_ds) {
		ds_handle_put(data->saved_ds);
		data->saved_ds = NULL;
	}

	if (data->saved_obj) {
		/* Release ref on old object */
		data->saved_obj->obj_ops.put_ref(data->saved_obj);
	}

	if (restore_op_ctx) {
		/* Restore op_ctx */
		op_ctx->ctx_export = current_export;
		op_ctx->fsal_export = current_export
					? current_export->fsal_export
					: NULL;
		*op_ctx->export_perms = current_export_perms;
	}

	data->saved_obj = obj;

	if (obj == NULL) {
		data->saved_filetype = NO_FILE_TYPE;
		return;
	}

	/* Get our ref on the new object */
	data->saved_obj->obj_ops.get_ref(data->saved_obj);

	/* Set the saved file type */
	data->saved_filetype = obj->type;
}

#endif				/* NFS_PROTO_DATA_H */
/** @} */
