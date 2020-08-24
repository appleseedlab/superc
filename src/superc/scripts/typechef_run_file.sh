#!/bin/bash

# xtc - The eXTensible Compiler
# Copyright (C) 2009-2012 New York University
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
# USA.


# This script runs the TypeChef Linux test case with either SuperC or
# TypeChef.  It produces total and per-file timing data.


TYPECHEF_LINUXVER=linux-2.6.33.3

# Get options.

# Defaults
system="TypeChef"
args= #empty
raw_mode= #empty
unconstrained= #empty
webfrontend= #empty

while getopts :a:t:ruw opt; do
    case $opt in
        a)
            args=$OPTARG
            ;;
        r)
            raw_mode=true
            ;;
        u)
            unconstrained=true
            ;;
        t)
            system=$OPTARG
            ;;
        w)
            webfrontend=true
            ;;
        \?)
            echo "Invalid argument: -$OPTARG"
            exit;
            ;;
        :)
            echo "-$OPTARG requires an argument."
            exit;
            ;;
    esac
done

shift $(($OPTIND - 1))


# Check that a filename was passed.

file=$1


# Check that a filename was passed.

if [ -z $file ]; then
    echo "USAGE: `basename $0` [-t SuperC|TypeChef] [-a args] file"
    echo ""
    echo "  Run SuperC or TypeChef on the TypeChef.  By default it uses the"
    echo "  partially-configured Linux settings."
    echo ""
    echo "FLAGS:"
    echo "  -t tool  Set the tool to be TypeChef (the default) or SuperC"
    echo "  -a args  Pass extra arguments when running the tool"
    echo "  -u       Don't constrain linux."
    echo "  -r       Raw mode: no extra flags for linux, e.g. -I paths."
    echo "  -w       Use TypeChef's web front end.  Forces raw mode."
    exit 0
fi

if [ ! -f $file ]; then
    echo "Invalid file \"$file\"."
    exit 0
fi

if [[ "$system" != "TypeChef" && "$system" != "SuperC" ]]; then
    echo "Please specify either \"-t TypeChef\" or \"-t Superc\"."
    exit 0
fi

if [[ "$system" != "TypeChef" && ! -z $webfrontend ]]; then
    echo "The option \"-w\" is only valid for \"-t TypeChef\" is specified."
    exit 0
fi

# Make sure the SuperC environment is set up.

if [ -z "$JAVA_DEV_ROOT" ]
then
    "please run env.sh first"
fi


# Make sure the linux source is there.

if [[ -z $webfrontend && ! -d "$TYPECHEF_LINUXVER" ]]
then
    echo "Please run ./prepareLinuxTestCase.sh from the TypeChef directory " \
        "first."
    exit 1
fi


# Set up TypeChef partial configuration.

srcPath=$PWD/$TYPECHEF_LINUXVER


flags() {
  name="$file"
  base="$(basename "$name")"
  if grep -q "arch/x86/boot" <<< "$name"; then
    extraFlag="-D _SETUP"
  elif grep -q "arch/x86/kvm" <<< "$name"; then
    extraFlag="-I $srcPath/virt/kvm -I $srcPath/arch/x86/kvm -I $srcPath"
  elif [ "$name" = "net/mac80211/driver-trace" ]; then
    extraFlag="-I $srcPath/net/mac80211"
  elif grep -q "fs/gfs2/" <<< "$name"; then
    extraFlag="-I $srcPath/fs/gfs2"
  elif grep -q "fs/ocfs2/" <<< "$name"; then
    extraFlag="-I $srcPath/fs/ocfs2 -D CATCH_BH_JBD_RACES"
  elif grep -q "fs/xfs/" <<< "$name"; then
    extraFlag="-I $srcPath/fs/xfs -I $srcPath/fs/xfs/linux-2.6"
  elif grep -q "fs/ntfs/" <<< "$name"; then
    extraFlag="-D NTFS_VERSION=\"\\\"2.1.29\"\\\" --include ntfs.h"
  elif grep -q "drivers/gpu/drm/" <<< "$name"; then
    extraFlag="-I $srcPath/include/drm"
  elif egrep -q "drivers/scsi/pcmcia/|drivers/usb/storage/" <<< "$name"; then
    extraFlag="-I $srcPath/drivers/scsi"
  elif grep -q "drivers/scsi/cxgb3i/" <<< "$name"; then
    extraFlag="-I $srcPath/drivers/net/cxgb3"
  elif grep -q "drivers/infiniband/hw/cxgb3/" <<< "$name"; then
    extraFlag="-I $srcPath/drivers/net/cxgb3"
  elif grep -q "drivers/net/skfp/" <<< "$name"; then
    extraFlag="-I $srcPath/drivers/net/skfp -D PCI -D MEM_MAPPED_IO"
  elif grep -q "drivers/staging/rt2860/" <<< "$name"; then
    extraFlag="-D LINUX -D AGGREGATION_SUPPORT -D PIGGYBACK_SUPPORT -D WMM_SUPPORT -D RTMP_MAC_PCI -D RTMP_PCI_SUPPORT -D RT2860 -D RTMP_RF_RW_SUPPORT -D RTMP_EFUSE_SUPPORT -D RT30xx -D RT3090 -D DBG"
  elif grep -q "drivers/staging/rt2870/" <<< "$name"; then
    extraFlag="-D LINUX -D AGGREGATION_SUPPORT -D PIGGYBACK_SUPPORT -D WMM_SUPPORT -D RTMP_MAC_USB -D RTMP_USB_SUPPORT -D RT2870 -D RTMP_TIMER_TASK_SUPPORT -D RTMP_RF_RW_SUPPORT -D RTMP_EFUSE_SUPPORT -D RT30xx -D RT3070 -D DBG"
  elif grep -q "drivers/staging/rtl8192e/" <<< "$name"; then
    extraFlag="-D RTL8192E -D THOMAS_TURBO -D ENABLE_DOT11D"
  elif [ "$name" = "drivers/net/wireless/iwlwifi/iwl-devtrace" ]; then
    extraFlag="-I $srcPath/drivers/net/wireless/iwlwifi/"
  elif grep -q "drivers/scsi/bfa/" <<< "$name"; then
    extraFlag=""
    for path in drivers/scsi/bfa drivers/scsi/bfa/include drivers/scsi/bfa/include/cna; do
      extraFlag="$extraFlag -I $srcPath/$path"
    done
  elif egrep -q "drivers/media/common/tuners/|drivers/staging/go7007/" <<< "$name"; then
    extraFlag=""
    for path in drivers/media/dvb/dvb-core drivers/media/dvb/frontends; do
      extraFlag="$extraFlag -I $srcPath/$path"
    done
    if grep -q "drivers/staging/go7007/" <<< "$name"; then
      extraFlag="$extraFlag -I $srcPath/drivers/media/dvb/dvb-usb"
    fi
  elif egrep -q "drivers/media/video/gspca/(gl860|m5602|stv06xx)/" <<< "$name"; then
    extraFlag="-I $srcPath/drivers/media/video/gspca"
  elif egrep -q "drivers/media/(dvb|video)/|drivers/staging/cx25821/" <<< "$name"; then
    extraFlag=""
    for path in drivers/media/dvb/dvb-core drivers/media/dvb/frontends drivers/media/common/tuners \
      drivers/ieee1394 drivers/media/video/bt8xx drivers/media/video; do
      extraFlag="$extraFlag -I $srcPath/$path"
    done
  else
    extraFlag=""
  fi
  # XXX: again, I need to specify $PWD, for the same bug as above.
  # "-I linux-2.6.33.3/include -I linux-2.6.33.3/arch/x86/include"


  # if [[ ! -z $unconstrained ]]; then
  #     echo "-I $srcPath/include -I $srcPath/arch/x86/include -D KBUILD_BASENAME=\"\\\"$base\\\"\" -D KBUILD_MODNAME=\"\\\"$base\\\"\""
  # else
  #     echo "$extraFlag -I $srcPath/include -I $srcPath/arch/x86/include -D __KERNEL__ -D CONFIG_AS_CFI=1 -D CONFIG_AS_CFI_SIGNAL_FRAME=1 -D KBUILD_BASENAME=\"\\\"$base\\\"\" -D KBUILD_MODNAME=\"\\\"$base\\\"\""
  # fi


  echo "$extraFlag -I $srcPath/include -I $srcPath/arch/x86/include -D __KERNEL__ -D CONFIG_AS_CFI=1 -D CONFIG_AS_CFI_SIGNAL_FRAME=1 -D KBUILD_BASENAME=\"\\\"$base\\\"\" -D KBUILD_MODNAME=\"\\\"$base\\\"\""
}


extraFlags="$(flags "$i")"

# From commit-id 043df2e6ad linuxTestCase.sh, the latest, but doesn't work.
# partialPreprocFlagsTypeChef="-c linux-redhat.properties -x CONFIG_ \
#   --typeSystemFeatureModelDimacs=2.6.33.3-2var.dimacs \
#   --include=completedConf.h \
#   --include=partialConf.h --openFeat openFeaturesList.txt \
#   $extraFlags"

# From commit-id 4b0f33fc0d linuxTestCase.sh, the second to latest.
partialPreprocFlagsTypeChef="-c linux-redhat.properties -x CONFIG_ \
  --include completedConf.h \
  --include partialConf.h --openFeat openFeaturesList.txt \
  --featureModelFExpr approx.fm \
  $extraFlags"



partialPreprocFlagsSuperC="\
-isystem systems/redhat/usr/lib/gcc/x86_64-redhat-linux/4.4.4/include \
-TypeChef-x CONFIG_ \
-include completedConf.h \
-include partialConf.h \
$extraFlags"

if [[ ! -z $raw_mode || ! -z $webfrontend ]]; then

    # Don't provide any linux flags.

    partialPreprocFlagsTypeChef=
    partialPreprocFlagsSuperC=


elif [[ ! -z $unconstrained && -z $webfrontend ]]; then

    # Keep linux includes but not the constraints.

    partialPreprocFlagsTypeChef="-c redhat.properties $extraFlags"

    partialPreprocFlagsSuperC="\
-isystem systems/redhat/usr/lib/gcc/x86_64-redhat-linux/4.4.4/include \
$extraFlags"
fi

javaOpts="-Xmx2G -Xms128m -Xss10m"

echo "Processing $file with $system"

if [ "$system" == "SuperC" ]; then
    # Run SuperC on the file.

    echo "# Flags: $partialPreprocFlagsSuperC $args $file" >&2

    java $javaOpts xtc.lang.cpp.SuperC -silent \
        $partialPreprocFlagsSuperC $args $file

else
    # Run TypeChef on the file.

    echo "# Flags: $partialPreprocFlagsTypeChef $args $file" >&2

    basePath=.

    if [ ! -z $webfrontend ]; then
        mainClass="de.fosd.typechef.linux.WebFrontend"
    else
        mainClass="de.fosd.typechef.linux.LinuxPreprocessorFrontend"
    fi

    ../TypeChef/typechef.sh --parse --lexNoStdout --no-warnings $partialPreprocFlagsTypeChef $args $file
fi








