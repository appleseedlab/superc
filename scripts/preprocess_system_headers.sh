#!/bin/bash

if [ $# -lt 1 ]; then
  echo -e "A tool to preprocess system headers."
  echo -e ""
  echo -e "USAGE: $(basename $0) outdir [ sysdirs ]"
  echo -e ""
  echo -e "\toutdir\t\tthe path to store the preprocessed headers"
  echo -e "\tsysdirs\t\t(optional) specify sysdirs, otherwise these will\n\t\t\tbe automatically collected from cpp -v"
  exit 0
elif [ $# -lt 2 ]; then
  # pattern-match the output of the preprocessor's verbose mode to get
  # the system include paths
  sysdirs="$(cat /dev/null | cpp -v |& sed -n '/#include <...> search starts here:/,/End of search list./p' | head -n-1 | tail -n+2)"
else
  sysdirs="${2}"
fi

headeroutdir="${1}"

# echo $headeroutdir
# echo $sysdirs
# exit 0

# emit the superc arguments to use the preprocessed headers
supercargs="${headeroutdir}/supercargs.txt"
echo -n "-nostdinc" > "${supercargs}"
for i in ${sysdirs}; do
  newsysdir="${headeroutdir}${i}"
  mkdir -p "${newsysdir}"
  echo -n " -isystem ${newsysdir}" >> "${supercargs}"
done
echo "" >> "${supercargs}"

# go over each header file in the sysdirs, preprocessor each one, and
# save it to an equivalently named file if it doesn't have an error
# (e.g., protected from direct inclusion with an #error directive)
for i in $(for i in ${sysdirs}; do ls $i/*.h; done); do
  outfile="${headeroutdir}/${i}";
  gcc -E "${i}" >/dev/null;
  errcode="${?}"
  if [[ "${errcode}" == "0" ]]; then
    gcc -E "${i}" > "${outfile}"
    echo "preprocessed header file: $i"
  else
    echo "skipping header with error: $i"
  fi
done

echo "some header files skipped due to errors.  this can happen, e.g.,
if the header has an #error directive intentionally preventing direct
inclusion or if there are missing headers."
