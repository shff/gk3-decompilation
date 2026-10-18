#!/usr/bin/perl

use strict;
use warnings;
use File::Find;
use File::Basename qw(dirname);
use File::Spec;

@ARGV == 1 or die "usage: $0 IDENTIFIER\n";
my ($identifier) = @ARGV;
$identifier =~ /\A[A-Za-z_][A-Za-z_0-9]*\z/
    or die "invalid C identifier: $identifier\n";

my $root = dirname(File::Spec->rel2abs($0));
my $found = 0;

find(
    {
        no_chdir => 1,
        wanted => sub {
            return unless -f $_ && /\.c\z/;
            return if /(?:^|\/)GK3R\.EXE\.c\z/;

            open my $file, '<', $_ or die "cannot read $_: $!\n";
            local $/;
            my $contents = <$file>;
            close $file or die "cannot close $_: $!\n";

            if ($contents =~ /\b\Q$identifier\E\b/) {
                $found = 1;
                $File::Find::prune = 1;
            }
        },
    },
    $root
);

print $found ? "true\n" : "false\n";
exit($found ? 0 : 1);
