static int (*check_part[])(struct parsed_partitions *, struct block_device *) = {
#ifdef CONFIG_ACORN_PARTITION_ICS
	adfspart_check_ICS,
#endif
#ifdef CONFIG_ACORN_PARTITION_POWERTEC
	adfspart_check_POWERTEC,
#endif
#ifdef CONFIG_ACORN_PARTITION_EESOX
	adfspart_check_EESOX,
#endif
#ifdef CONFIG_ACORN_PARTITION_CUMANA
	adfspart_check_CUMANA,
#endif
#ifdef CONFIG_ACORN_PARTITION_ADFS
	adfspart_check_ADFS,
#endif
#ifdef CONFIG_EFI_PARTITION
	efi_partition,
#endif
#ifdef CONFIG_SGI_PARTITION
	sgi_partition,
#endif
#ifdef CONFIG_LDM_PARTITION
	ldm_partition,
#endif
/* #ifdef CONFIG_MSDOS_PARTITION */
/* 	msdos_partition, */
/* #endif */
/* #ifdef CONFIG_OSF_PARTITION */
/* 	osf_partition, */
/* #endif */
/* #ifdef CONFIG_SUN_PARTITION */
/* 	sun_partition, */
/* #endif */
/* #ifdef CONFIG_AMIGA_PARTITION */
/* 	amiga_partition, */
/* #endif */
/* #ifdef CONFIG_ATARI_PARTITION */
/* 	atari_partition, */
/* #endif */
/* #ifdef CONFIG_MAC_PARTITION */
/* 	mac_partition, */
/* #endif */
/* #ifdef CONFIG_ULTRIX_PARTITION */
/* 	ultrix_partition, */
/* #endif */
/* #ifdef CONFIG_IBM_PARTITION */
/* 	ibm_partition, */
/* #endif */
/* #ifdef CONFIG_KARMA_PARTITION */
/* 	karma_partition, */
/* #endif */
/* #ifdef CONFIG_SYSV68_PARTITION */
/* 	sysv68_partition, */
/* #endif */
	NULL
};
