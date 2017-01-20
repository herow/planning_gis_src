#!/usr/bin/perl 
###########################################################################
#    fixdiff.pl
#    ---------------------
#    begin                : May 2008
#    copyright            : (C) 2008 by Juergen E. Fischer
#    email                : jef at norbit dot de
###########################################################################
#                                                                         #
#   This program is free software; you can redistribute it and/or modify  #
#   it under the terms of the GNU General Public License as published by  #
#   the Free Software Foundation; either version 2 of the License, or     #
#   (at your option) any later version.                                   #
#                                                                         #
###########################################################################

# NAME
#   fixdiff.pl - fix line endings in svn diff to match lineending of existing files
# SYNOPSIS
#   perl fixdiff.pl a.diff | patch -p0 ...
# DESCRIPTION:
#   parse diff and modify the hunks to match the line ending of the target files
#   This is useful, when the compared trees to generate the diff are on a
#   different architecture than that of the one where the patch is to be
#   applied.

use strict;
use warnings;

my $dos;

while(<>) {
   if( /^Index: (.*)\n/ ) {
      my $file=$1;
      $dos=0;

      if(-f $file) {
        open F, $file;
        binmode(F);
        $dos=1 if scalar(<F>) =~ /\r\n$/;
        close F;

        #warn "$file in DOS mode!" if $dos;
      } else {
          warn "$file not found.";
      }
   } elsif(/^$/) {
      # skip empty lines
      next;
   } elsif(/^===================================================================/ ||
           /^---/ ||
           /^\+\+\+/ ||
           /^@@/) {
      print;
   } elsif($dos && !/\r\n$/) {
      chop;
      print "$_\r\n";
   } elsif(!$dos && /\r\n$/) {
      chop;
      chop;
      print "$_\n";
   } else {
      print;
   }
}
