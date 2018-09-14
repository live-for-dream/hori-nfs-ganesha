/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "config.h"
#include "gsh_rpc.h"
#include "mount.h"
#include "nfs23.h"
#include "nfs_fh.h"

bool xdr_mountstat3(xdrs, objp)
register XDR *xdrs;
mountstat3 *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int __attribute__ ((__unused__)) * buf;
#else
	register long __attribute__ ((__unused__)) * buf;
#endif

	if (!inline_xdr_enum(xdrs, (enum_t *) objp))
		return (false);
	return (true);
}

bool xdr_fhandle3(xdrs, objp)
register XDR *xdrs;
fhandle3 *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int __attribute__ ((__unused__)) * buf;
#else
	register long __attribute__ ((__unused__)) * buf;
#endif
	if (!inline_xdr_bytes
	    (xdrs, (char **)&objp->fhandle3_val, (u_int *) & objp->fhandle3_len,
	     NFS3_FHSIZE))
		return (false);

	return (true);
}

bool xdr_dirpath(xdrs, objp)
register XDR *xdrs;
dirpath *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int __attribute__ ((__unused__)) * buf;
#else
	register long __attribute__ ((__unused__)) * buf;
#endif

	if (!inline_xdr_string(xdrs, objp, MNTPATHLEN))
		return (false);
	return (true);
}

bool xdr_name(xdrs, objp)
register XDR *xdrs;
name *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int __attribute__ ((__unused__)) * buf;
#else
	register long __attribute__ ((__unused__)) * buf;
#endif

	if (!inline_xdr_string(xdrs, objp, MNTNAMLEN))
		return (false);
	return (true);
}

bool xdr_groups(xdrs, objp)
register XDR *xdrs;
groups *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int __attribute__ ((__unused__)) * buf;
#else
	register long __attribute__ ((__unused__)) * buf;
#endif

	if (!xdr_pointer
	    (xdrs, (char **)objp, sizeof(struct groupnode),
	     (xdrproc_t) xdr_groupnode))
		return (false);
	return (true);
}

bool xdr_groupnode(xdrs, objp)
register XDR *xdrs;
groupnode *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int __attribute__ ((__unused__)) * buf;
#else
	register long __attribute__ ((__unused__)) * buf;
#endif

	if (!xdr_name(xdrs, &objp->gr_name))
		return (false);
	if (!xdr_groups(xdrs, &objp->gr_next))
		return (false);
	return (true);
}

bool xdr_exports(xdrs, objp)
register XDR *xdrs;
exports *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int __attribute__ ((__unused__)) * buf;
#else
	register long __attribute__ ((__unused__)) * buf;
#endif

	if (!xdr_pointer
	    (xdrs, (char **)objp, sizeof(struct exportnode),
	     (xdrproc_t) xdr_exportnode))
		return (false);
	return (true);
}

bool xdr_exportnode(xdrs, objp)
register XDR *xdrs;
exportnode *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int __attribute__ ((__unused__)) * buf;
#else
	register long __attribute__ ((__unused__)) * buf;
#endif

	if (!xdr_dirpath(xdrs, &objp->ex_dir))
		return (false);
	if (!xdr_groups(xdrs, &objp->ex_groups))
		return (false);
	if (!xdr_exports(xdrs, &objp->ex_next))
		return (false);
	return (true);
}

bool xdr_mountlist(xdrs, objp)
register XDR *xdrs;
mountlist *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int __attribute__ ((__unused__)) * buf;
#else
	register long __attribute__ ((__unused__)) * buf;
#endif

	if (!xdr_pointer
	    (xdrs, (char **)objp, sizeof(struct mountbody),
	     (xdrproc_t) xdr_mountbody))
		return (false);
	return (true);
}

bool xdr_mountbody(xdrs, objp)
register XDR *xdrs;
mountbody *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int __attribute__ ((__unused__)) * buf;
#else
	register long __attribute__ ((__unused__)) * buf;
#endif

	if (!xdr_name(xdrs, &objp->ml_hostname))
		return (false);
	if (!xdr_dirpath(xdrs, &objp->ml_directory))
		return (false);
	if (!xdr_mountlist(xdrs, &objp->ml_next))
		return (false);
	return (true);
}

bool xdr_mountres3_ok(xdrs, objp)
register XDR *xdrs;
mountres3_ok *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int __attribute__ ((__unused__)) * buf;
#else
	register long __attribute__ ((__unused__)) * buf;
#endif

	if (!xdr_fhandle3(xdrs, &objp->fhandle))
		return (false);
	if (!xdr_array
	    (xdrs, (char **)&objp->auth_flavors.auth_flavors_val,
	     &objp->auth_flavors.auth_flavors_len, XDR_ARRAY_MAXLEN,
	     sizeof(int), (xdrproc_t) xdr_int))
		return (false);
	return (true);
}

bool xdr_mountres3(xdrs, objp)
register XDR *xdrs;
mountres3 *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int __attribute__ ((__unused__)) * buf;
#else
	register long __attribute__ ((__unused__)) * buf;
#endif

	if (!xdr_mountstat3(xdrs, &objp->fhs_status))
		return (false);
	switch (objp->fhs_status) {
	case MNT3_OK:
		if (!xdr_mountres3_ok(xdrs, &objp->mountres3_u.mountinfo))
			return (false);
		break;
	default:
		return (true);
		break;
	}
	return (true);
}
