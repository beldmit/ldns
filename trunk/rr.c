/*
 * rr.c
 *
 * access function for ldns_rr
 *
 * a Net::DNS like library for C
 *
 * (c) NLnet Labs, 2004
 *
 * See the file LICENSE for the license
 */

#include <config.h>

#include <limits.h>

#include <ldns/rr.h>

#include "util.h"

/**
 * create a new rr structure.
 */
ldns_rr *
ldns_rr_new(void)
{
	ldns_rr *rr;
	rr = MALLOC(ldns_rr);
        if (!rr) {
                return NULL;
	}
	
	ldns_rr_set_rd_count(rr, 0);
	rr->_rdata_fields = NULL; /* XXX */
        return rr;
}

/**
 * set the owner in the rr structure
 */
void
ldns_rr_set_owner(ldns_rr *rr, uint8_t *owner)
{
	rr->_owner = owner;
}

/**
 * set the owner in the rr structure
 */
void
ldns_rr_set_ttl(ldns_rr *rr, uint16_t ttl)
{
	rr->_ttl = ttl;
}

/**
 * set the rd_count in the rr
 */
void
ldns_rr_set_rd_count(ldns_rr *rr, uint16_t count)
{
	rr->_rd_count = count;
}

/**
 * set the class in the rr
 */
void
ldns_rr_set_class(ldns_rr *rr, ldns_class klass)
{
	rr->_klass = klass;
}

/**
 * set rd_field member in the rr, it will be 
 * placed in the next available spot
 */
bool
ldns_rr_push_rdf(ldns_rr *rr, ldns_rdf *f)
{
	uint16_t rd_count;
	ldns_rdf **rdata_fields;
	
	rd_count = ldns_rr_rd_count(rr);
	
	/* grow the array */
	rdata_fields = XREALLOC(
		rr->_rdata_fields, ldns_rdf *, rd_count + 1);
	if (!rdata_fields) {
		return false;
	}
	
	/* add the new member */
	rr->_rdata_fields = rdata_fields;
	rr->_rdata_fields[rd_count] = f;

	ldns_rr_set_rd_count(rr, rd_count + 1);
	return true;
}

/**
 * return the owner name of an rr structure
 */
uint8_t *
ldns_rr_owner(ldns_rr *rr)
{
	return rr->_owner;
}

/**
 * return the owner name of an rr structure
 */
uint8_t
ldns_rr_ttl(ldns_rr *rr)
{
	return rr->_ttl;
}

/**
 * return the rd_count of an rr structure
 */
uint16_t
ldns_rr_rd_count(ldns_rr *rr)
{
	return rr->_rd_count;
}

static const ldns_rdf_type type_0_wireformat[] = { RDF_TYPE_UNKNOWN };
static const ldns_rdf_type type_a_wireformat[] = { RDF_TYPE_A };
static const ldns_rdf_type type_ns_wireformat[] = { RDF_TYPE_DNAME };
static const ldns_rdf_type type_md_wireformat[] = { RDF_TYPE_DNAME };
static const ldns_rdf_type type_mf_wireformat[] = { RDF_TYPE_DNAME };
static const ldns_rdf_type type_cname_wireformat[] = { RDF_TYPE_DNAME };
static const ldns_rdf_type type_soa_wireformat[] = {
	RDF_TYPE_DNAME, RDF_TYPE_DNAME, RDF_TYPE_INT32, RDF_TYPE_INT32,
	RDF_TYPE_INT32, RDF_TYPE_INT32, RDF_TYPE_INT32
};
static const ldns_rdf_type type_mb_wireformat[] = { RDF_TYPE_DNAME };
static const ldns_rdf_type type_mg_wireformat[] = { RDF_TYPE_DNAME };
static const ldns_rdf_type type_mr_wireformat[] = { RDF_TYPE_DNAME };
static const ldns_rdf_type type_wks_wireformat[] = {
	RDF_TYPE_A, RDF_TYPE_SERVICE
};
static const ldns_rdf_type type_ptr_wireformat[] = { RDF_TYPE_DNAME };
static const ldns_rdf_type type_hinfo_wireformat[] = {
	RDF_TYPE_STR, RDF_TYPE_STR
};
static const ldns_rdf_type type_minfo_wireformat[] = {
	RDF_TYPE_DNAME, RDF_TYPE_DNAME
};
static const ldns_rdf_type type_mx_wireformat[] = {
	RDF_TYPE_INT8, RDF_TYPE_DNAME
};
static const ldns_rdf_type type_rp_wireformat[] = {
	RDF_TYPE_DNAME, RDF_TYPE_DNAME
};
static const ldns_rdf_type type_afsdb_wireformat[] = {
	RDF_TYPE_INT8, RDF_TYPE_DNAME
};
static const ldns_rdf_type type_x25_wireformat[] = { RDF_TYPE_STR };
static const ldns_rdf_type type_isdn_wireformat[] = {
	RDF_TYPE_STR, RDF_TYPE_STR
};
static const ldns_rdf_type type_rt_wireformat[] = {
	RDF_TYPE_INT8, RDF_TYPE_DNAME
};
static const ldns_rdf_type type_sig_wireformat[] = {
	RDF_TYPE_INT8, RDF_TYPE_INT8, RDF_TYPE_INT8, RDF_TYPE_INT32,
	RDF_TYPE_INT32, RDF_TYPE_INT32, RDF_TYPE_INT16,
	RDF_TYPE_DNAME, RDF_TYPE_B64
};
static const ldns_rdf_type type_key_wireformat[] = {
	RDF_TYPE_INT16, RDF_TYPE_INT8, RDF_TYPE_INT8, RDF_TYPE_B64
};
static const ldns_rdf_type type_px_wireformat[] = {
	RDF_TYPE_INT16, RDF_TYPE_DNAME, RDF_TYPE_DNAME
};
static const ldns_rdf_type type_aaaa_wireformat[] = { RDF_TYPE_AAAA };
static const ldns_rdf_type type_loc_wireformat[] = { RDF_TYPE_LOC };
static const ldns_rdf_type type_nxt_wireformat[] = {
	RDF_TYPE_DNAME, RDF_TYPE_UNKNOWN
};
static const ldns_rdf_type type_srv_wireformat[] = {
	RDF_TYPE_INT16, RDF_TYPE_INT16, RDF_TYPE_INT16, RDF_TYPE_DNAME
};
static const ldns_rdf_type type_naptr_wireformat[] = {
	RDF_TYPE_INT16, RDF_TYPE_INT16, RDF_TYPE_STR, RDF_TYPE_STR, RDF_TYPE_STR, RDF_TYPE_DNAME
};
static const ldns_rdf_type type_kx_wireformat[] = {
	RDF_TYPE_INT16, RDF_TYPE_DNAME
};
static const ldns_rdf_type type_cert_wireformat[] = {
	 RDF_TYPE_CERT, RDF_TYPE_INT16, RDF_TYPE_ALG, RDF_TYPE_B64
};
static const ldns_rdf_type type_dname_wireformat[] = { RDF_TYPE_DNAME };
static const ldns_rdf_type type_ds_wireformat[] = {
	RDF_TYPE_INT16, RDF_TYPE_INT8, RDF_TYPE_INT8, RDF_TYPE_HEX
};
static const ldns_rdf_type type_sshfp_wireformat[] = {
	RDF_TYPE_INT8, RDF_TYPE_INT8, RDF_TYPE_HEX
};
static const ldns_rdf_type type_rrsig_wireformat[] = {
	RDF_TYPE_TYPE, RDF_TYPE_INT8, RDF_TYPE_INT8, RDF_TYPE_INT32,
	RDF_TYPE_INT32, RDF_TYPE_INT32, RDF_TYPE_INT16, RDF_TYPE_DNAME, RDF_TYPE_B64
};
static const ldns_rdf_type type_nsec_wireformat[] = {
	RDF_TYPE_DNAME, RDF_TYPE_NSEC
};
static const ldns_rdf_type type_dnskey_wireformat[] = {
	RDF_TYPE_INT16, RDF_TYPE_INT8, RDF_TYPE_ALG, RDF_TYPE_B64
};

static ldns_rr_descriptor rdata_field_descriptors[] = {
	/* 0 */
	{ 0, NULL, 1, 1, type_0_wireformat, RDF_TYPE_NONE },
	/* 1 */
	{ TYPE_A, "A", 1, 1, type_a_wireformat, RDF_TYPE_NONE },
	/* 2 */
	{ TYPE_NS, "NS", 1, 1, type_ns_wireformat, RDF_TYPE_NONE },
	/* 3 */
	{ TYPE_MD, "MD", 1, 1, type_md_wireformat, RDF_TYPE_NONE },
	/* 4 */ 
	{ TYPE_MF, "MF", 1, 1, type_mf_wireformat, RDF_TYPE_NONE },
	/* 5 */
	{ TYPE_CNAME, "CNAME", 1, 1, type_cname_wireformat, RDF_TYPE_NONE },
	/* 6 */
	{ TYPE_SOA, "SOA", 7, 7, type_soa_wireformat, RDF_TYPE_NONE },
	/* 7 */
	{ TYPE_MB, "MB", 1, 1, type_mb_wireformat, RDF_TYPE_NONE },
	/* 8 */
	{ TYPE_MG, "MG", 1, 1, type_mg_wireformat, RDF_TYPE_NONE },
	/* 9 */
	{ TYPE_MR, "MR", 1, 1, type_mr_wireformat, RDF_TYPE_NONE },
	/* 10 */
	{ TYPE_NULL, "NULL", 1, 1, type_0_wireformat, RDF_TYPE_NONE },
	/* 11 */
	{ TYPE_WKS, "WKS", 2, 2, type_wks_wireformat, RDF_TYPE_NONE },
	/* 12 */
	{ TYPE_PTR, "PTR", 1, 1, type_ptr_wireformat, RDF_TYPE_NONE },
	/* 13 */
	{ TYPE_HINFO, "HINFO", 2, 2, type_hinfo_wireformat, RDF_TYPE_NONE },
	/* 14 */
	{ TYPE_MINFO, "MINFO", 2, 2, type_minfo_wireformat, RDF_TYPE_NONE },
	/* 15 */
	{ TYPE_MX, "MX", 2, 2, type_mx_wireformat, RDF_TYPE_NONE },
	/* 16 */
	{ TYPE_TXT, "TXT", 1, 0, NULL, RDF_TYPE_STR },
	/* 17 */
	{ TYPE_RP, "RP", 2, 2, type_rp_wireformat, RDF_TYPE_NONE },
	/* 18 */
	{ TYPE_AFSDB, "AFSDB", 2, 2, type_afsdb_wireformat, RDF_TYPE_NONE },
	/* 19 */
	{ TYPE_X25, "X25", 1, 1, type_x25_wireformat, RDF_TYPE_NONE },
	/* 20 */
	{ TYPE_ISDN, "ISDN", 1, 2, type_isdn_wireformat, RDF_TYPE_NONE },
	/* 21 */
	{ TYPE_RT, "RT", 2, 2, type_rt_wireformat, RDF_TYPE_NONE },
	/* 22 */
	{ TYPE_NSAP, "NSAP", 1, 1, type_0_wireformat, RDF_TYPE_NONE },
	/* 23 */
	{ 23, NULL, 1, 1, type_0_wireformat, RDF_TYPE_NONE },
	/* 24 */
	{ TYPE_SIG, "SIG", 9, 9, type_sig_wireformat, RDF_TYPE_NONE },
	/* 25 */
	{ TYPE_KEY, "KEY", 4, 4, type_key_wireformat, RDF_TYPE_NONE },
	/* 26 */
	{ TYPE_PX, "PX", 3, 3, type_px_wireformat, RDF_TYPE_NONE },
	/* 27 */
	{ 27, NULL, 1, 1, type_0_wireformat, RDF_TYPE_NONE },
	/* 28 */
	{ TYPE_AAAA, "AAAA", 1, 1, type_aaaa_wireformat, RDF_TYPE_NONE },
	/* 29 */
	{ TYPE_LOC, "LOC", 1, 1, type_loc_wireformat, RDF_TYPE_NONE },
	/* 30 */
	{ TYPE_NXT, "NXT", 2, 2, type_nxt_wireformat, RDF_TYPE_NONE },
	/* 31 */
	{ 31, NULL, 1, 1, type_0_wireformat, RDF_TYPE_NONE },
	/* 32 */
	{ 32, NULL, 1, 1, type_0_wireformat, RDF_TYPE_NONE },
	/* 33 */
	{ TYPE_SRV, "SRV", 4, 4, type_srv_wireformat, RDF_TYPE_NONE },
	/* 34 */
	{ 34, NULL, 1, 1, type_0_wireformat, RDF_TYPE_NONE },
	/* 35 */
	{ TYPE_NAPTR, "NAPTR", 6, 6, type_naptr_wireformat, RDF_TYPE_NONE },
	/* 36 */
	{ TYPE_KX, "KX", 2, 2, type_kx_wireformat, RDF_TYPE_NONE },
	/* 37 */
	{ TYPE_CERT, "CERT", 4, 4, type_cert_wireformat, RDF_TYPE_NONE },
	/* 38 */
	{ 38, NULL, 1, 1, type_0_wireformat, RDF_TYPE_NONE },
	/* 39 */
	{ TYPE_DNAME, "DNAME", 1, 1, type_dname_wireformat, RDF_TYPE_NONE },
	/* 40 */
	{ 40, NULL, 1, 1, type_0_wireformat, RDF_TYPE_NONE },
	/* 41 */
	{ TYPE_OPT, "OPT", 1, 1, type_0_wireformat, RDF_TYPE_NONE },
	/* 42 */
	{ TYPE_APL, "APL", 0, 0, NULL, RDF_TYPE_APL },
	/* 43 */
	{ TYPE_DS, "DS", 4, 4, type_ds_wireformat, RDF_TYPE_NONE },
	/* 44 */
	{ TYPE_SSHFP, "SSHFP", 3, 3, type_sshfp_wireformat, RDF_TYPE_NONE },
	/* 45 */
	{ 45, NULL, 1, 1, type_0_wireformat, RDF_TYPE_NONE },
	/* 46 */
	{ TYPE_RRSIG, "RRSIG", 9, 9, type_rrsig_wireformat, RDF_TYPE_NONE },
	/* 47 */
	{ TYPE_NSEC, "NSEC", 2, 2, type_nsec_wireformat, RDF_TYPE_NONE },
	/* 48 */
	{ TYPE_DNSKEY, "DNSKEY", 4, 4, type_dnskey_wireformat, RDF_TYPE_NONE }
};

#define RDATA_FIELD_DESCRIPTORS_COUNT \
	(sizeof(rdata_field_descriptors)/sizeof(rdata_field_descriptors[0]))

const ldns_rr_descriptor *
ldns_rr_descript(uint16_t type)
{
	if (type < RDATA_FIELD_DESCRIPTORS_COUNT) {
		return &rdata_field_descriptors[type];
	} else {
		return &rdata_field_descriptors[0];
	}
}

size_t
ldns_rr_descriptor_minimum(ldns_rr_descriptor *descriptor)
{
	return descriptor->_minimum;
}

size_t
ldns_rr_descriptor_maximum(ldns_rr_descriptor *descriptor)
{
	if (descriptor->_variable != RDF_TYPE_NONE) {
		/* XXX: Should really be SIZE_MAX... bad FreeBSD.  */
		return UINT_MAX;
	} else {
		return descriptor->_maximum;
	}
}

ldns_rdf_type
ldns_rr_descriptor_field_type(ldns_rr_descriptor *descriptor,
                              size_t index)
{
	assert(descriptor != NULL);
	assert(index < descriptor->_maximum
	       || descriptor->_variable != RDF_TYPE_NONE);
	if (index < descriptor->_maximum) {
		return descriptor->_wireformat[index];
	} else {
		return descriptor->_variable;
	}
}

/* TODO: general rdata2str or dname2str, with error
         checks and return status etc */
/* this is temp function for debugging wire2rr */
/* do NOT pass compressed data here :p */
void
ldns_dname2str(char *dest, uint8_t *dname)
{
	/* can we do with 1 pos var? or without at all? */
	uint8_t src_pos = 0;
	uint8_t dest_pos = 0;
	uint8_t len;
	len = dname[src_pos];
	while (len > 0) {
		src_pos++;
		memcpy(&dest[dest_pos], &dname[src_pos], len);
		dest_pos += len;
		src_pos += len;
		len = dname[src_pos];
		dest[dest_pos] = '.';
		dest_pos++;
	}
	dest_pos++;
	dest[dest_pos] = '\0';
}

/* TODO: is there a better place for this function?
         status_type return and remove printfs
         #defines */
size_t
ldns_wire2dname(uint8_t *dname, const uint8_t *wire, size_t max, size_t *pos)
{
	uint8_t label_size;
	uint16_t pointer_target;
	uint8_t *pointer_target_buf;
	size_t dname_pos = 0;
	size_t compression_pos = 0;

	if (*pos > max) {
		/* TODO set error */
		return 0;
	}
	
	label_size = wire[*pos];
	while (label_size > 0) {
		/* compression */
		if (label_size >= 192) {
			if (compression_pos == 0) {
				compression_pos = *pos + 2;
			}

			/* remove first two bits */
			/* TODO: can this be done in a better way? */
			pointer_target_buf = malloc(2);
			pointer_target_buf[0] = wire[*pos] & 63;
			pointer_target_buf[1] = wire[*pos+1];
			memcpy(&pointer_target, pointer_target_buf, 2);
			pointer_target = ntohs(pointer_target);

			if (pointer_target == 0) {
				fprintf(stderr, "POINTER TO 0\n");
				return 0;
			} else if (pointer_target > max) {
				fprintf(stderr, "POINTER TO OUTSIDE PACKET\n");
				return 0 ;
			}
			*pos = pointer_target;
			label_size = wire[*pos];
		}
		
		if (label_size > MAXLABELLEN) {
			/* TODO error: label size too large */
			fprintf(stderr, "LABEL SIZE ERROR: %d\n",
			        (int) label_size);
			return 0;
		}
		if (*pos + label_size > max) {
			/* TODO error: out of packet data */
			fprintf(stderr, "MAX PACKET ERROR: %d\n",
			        (int) (*pos + label_size));
		}
		
		dname[dname_pos] = label_size;
		dname_pos++;
		*pos = *pos + 1;
		memcpy(&dname[dname_pos], &wire[*pos], label_size);
		dname_pos += label_size;
		*pos = *pos + label_size;
		label_size = wire[*pos];
	}

	if (compression_pos > 0) {
		*pos = compression_pos;
	} else {
		*pos = *pos + 1;
	}
	return *pos;
}

/* TODO: ldns_status_type and error checking 
         defines for constants?
         enum for sections? 
         remove owner print debug message
         can *pos be incremented at READ_INT? or maybe use something like
         RR_CLASS(wire)?
*/
size_t
ldns_wire2rr(ldns_rr *rr, const uint8_t *wire, size_t max, 
             size_t *pos, int section)
{
	uint8_t *owner = malloc(MAXDOMAINLEN);
	char *owner_str = malloc(MAXDOMAINLEN);
	uint16_t rd_length;

	(void) ldns_wire2dname(owner, wire, max, pos);

	ldns_rr_set_owner(rr, owner);
	
	ldns_dname2str(owner_str, owner);
	printf("owner: %s\n", owner_str);
	FREE(owner_str);	
	
	ldns_rr_set_class(rr, read_uint16(&wire[*pos]));
	*pos = *pos + 2;
	/*
	ldns_rr_set_type(rr, read_uint16(&wire[*pos]));
	*/
	*pos = *pos + 2;

	if (section > 0) {
		ldns_rr_set_ttl(rr, read_uint32(&wire[*pos]));	
		*pos = *pos + 4;
		rd_length = read_uint16(&wire[*pos]);
		*pos = *pos + 2;
		/* TODO: wire2rdata */
		*pos = *pos + rd_length;
	}

	return (size_t) 0;
}



