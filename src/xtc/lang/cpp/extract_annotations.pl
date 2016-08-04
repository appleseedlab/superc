#!/usr/bin/perl -w

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


# This script extracts grammar annotations of the form

# nonterminal: /* annotation, annotation, ... */

# from a bison grammar.  The output is passed to ActionGenerator for
# automated AST node handling.


my %valid_annotations
    = map { $_ => 1 } ( "list", "layout", "action", "passthrough", "complete",
                        "void");
my $name_annotation = "name";


while(<STDIN>) {
    my($line) = $_;
    my($text) = $line;
    # Look for ^NAME ... /** ... **/
    if ($text =~ m/^(.*)\/\*\*([^\*]+)\*\*\//) {
        $symbol = $1;
        $annotations = $2;
        
        if ($symbol =~ m/^([\w\d\._]+):/) {
            $symbol = $1;
        } elsif ($symbol =~ m/^%token ([\w\d\._]+)/) {
            $symbol = $1;
        } else {
            $symbol = "";
        }

        if (length($symbol) > 0) {
            @a = split(/,/, $annotations);
            for my $annotation (@a) {
                $annotation =~ s/^\s*(.*?)\s*$/$1/;  # strip whitespace
                if ($annotation =~ m/^($name_annotation)\((.+)\)$/) {
                    # a name annotation
                    $annotation = $1;
                    $parameter = $2;
                    print "$symbol $annotation $parameter\n";
                } elsif (exists($valid_annotations{$annotation})) {
                    # all other annotations
                    print "$symbol $annotation\n"
                } else {
                    print STDERR
                        "warning: invalid annotation name $annotation\n";
                }
            }
        }
    }
}

#cat c.y | grep '^[A-Za-z0-9._]*: */\*\* *list *\*\*/' | awk -F: '{print $1, "list"}'
#cat c.y | grep '^[A-Za-z0-9._]*: */\*\* *action *\*\*/' | awk -F: '{print $1, "action"}'
#cat c.y | grep '^%token *[A-Za-z0-9._]* */\*\* *layout *\*\*/' | awk '{print $2, "layout"}'
#cat c.y | grep '^[A-Za-z0-9._]*: */\*\* *passthrough *\*\*/' | awk -F: '{print $1, "passthrough"}'

