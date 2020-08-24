if [ ${#} -lt 1 ]; then
    echo "USAGE: $(basename ${0}) grammar.y"
    exit 1
fi

yfile="${1}"
prefix="${yfile%.y}"
tabfile="${prefix}.tab.c"

if [ ! -f ${yfile} ]; then
    echo "no such grammar file \"${yfile}\""
    exit 1
fi

if [ ! -f ${tabfile} ]; then
    echo "please first generate the bison parser with \"bison -o ${tabfile} ${yfile}\""
    exit 1
fi

prol_beg="$(grep -n '^%{' ${yfile} | cut -d: -f1)"
prol_end="$(grep -n '^%}' ${yfile} | cut -d: -f1)"
edlm_cnt="$(grep -n '^%%' ${yfile} | wc -l)"
epil_beg="$(grep -n '^%%' ${yfile} | tail -n1 | cut -d: -f1)"

if [ -z ${prol_beg} ]; then
    echo "missing prologue in ${yfile}"
    exit 1
fi

if [ ${edlm_cnt} -lt 2 ]; then
    echo "missing epilogue in ${yfile}"
    exit 1
fi

bison -o ${tabfile} ${yfile}
csplit -f ${tabfile}. ${tabfile} "/^#line ${prol_beg} \"${yfile}\"/1" "/./$((prol_end-prol_beg))" '/  switch (yyn)/2' '/      default: break;/-2' "/^#line ${epil_beg} \"${yfile}\"/1" > /dev/null
cat ${tabfile}.01 | grep -v "^#line" > ${prefix}.prologue
cat ${tabfile}.03 | grep -v "^#line" > ${prefix}.action_switches
cat ${tabfile}.05 | grep -v "^#line" > ${prefix}.epilogue
cat ${tabfile}.00 ${tabfile}.02 ${tabfile}.04 > ${prefix}.bison_content
rm  ${tabfile}.00 ${tabfile}.01 ${tabfile}.02 ${tabfile}.03 ${tabfile}.04 ${tabfile}.05
