static int check_part[]={
#ifdef CONFIG_ACORN_PARTITION_ICS
1,
#endif
#ifdef CONFIG_ACORN_PARTITION_POWERTEC
2,
#endif
#ifdef CONFIG_ACORN_PARTITION_EESOX
3,
#endif
/* 12 more conditional array entries... */
NULL
};

