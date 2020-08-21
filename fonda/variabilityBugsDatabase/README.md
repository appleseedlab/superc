All the files in this database were taken from here: http://vbdb.itu.dk/database.html

The files represent the Simplified Bug (if it exists) found under each example.
The names of the file is either based off of the function or configuration option which is relavent to the bug,
with priority given to if that name exists in the title description.

--Notes:

BUILD_LIBBUSYBOX does not have a simplified bug

The following files can't compile due to their errors
APACHE/APR_INET6 --requires APR_HAVE_IPV6 to be	on
APACHE/apr_signal_block.c --requires SIGPIPE to	be on
APACHE/ap_scoreboard_shm.c --requires APR_HAS_SHARED_MEMORY to be on
APACHE/SSL_PROTOCOL_TLSV1_1.c --requires HAVE_TLSV1_X to be on
APACHE/SSLSrvConfigRec.c --requires HAVE_FIPS to be on
BUSYBOX/CONFIG_FEATURE_HTTPD_GZIP.c --lot odd here. Two	uses that are undef, but also constant error in
malloc?
BUSYBOX/k_crcs.c --k_crcs not always def
BUSYBOX/TIME_MASK.c --TIME_MASK	not always def
LINUX/TRACING.c --function has different args
MARLIN/ENABLE_AUTO_BED_LEVELING.c --ENABLE_AUTO_BED_LEVELING must always be on
MARLIN/SERIAL_ECHOPAIR.c --configPrintSettings not always def
MARLIN/ULTRA_LCD_N_SDSUPPORT.c --dif arg num conditionally


