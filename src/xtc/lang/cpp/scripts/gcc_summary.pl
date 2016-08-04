#!/usr/bin/perl -w

$filename = "";
$parser = 0;
$preprocessor = 0;
$lexer = 0;

while ($line=<>) {
    if ($line =~ m/^Processing (.*)$/) {
        if ($filename ne "") {
            $preprocessorlex = $preprocessor + $lexer;
            $parserpreproclex = $parser + $preprocessorlex;
            print "gcc_time $filename $parserpreproclex $preprocessorlex $lexer\n";
        }
        $filename = $1;
        $parser = 0;
        $preprocessor = 0;
        $lexer = 0;
    } elsif ($line =~ m/(parser|preprocessing|lexical analysis).*(\d+\.?\d+[^.]) \(\d+%\) wall/) {
        $type=$1;
        $val=$2;
        if ($type eq "parser") {
            $parser = $val;
        } elsif ($type eq "preprocessing") {
            $preprocessor = $val;
        } elsif ($type eq "lexical analysis") {
            $lexer = $val;
        }
    }
}
