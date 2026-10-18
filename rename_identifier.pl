#!/usr/bin/perl

use strict;
use warnings;
use File::Find;
use File::Basename qw(dirname);
use File::Spec;

@ARGV == 2 or die "usage: $0 OLD_IDENTIFIER NEW_IDENTIFIER\n";
my ($old, $new) = @ARGV;
for my $identifier ($old, $new) {
    $identifier =~ /\A[A-Za-z_][A-Za-z_0-9]*\z/
        or die "invalid C identifier: $identifier\n";
}
$old ne $new or die "old and new identifiers are identical\n";

my $root = dirname(File::Spec->rel2abs($0));
my @files;
find(
    {
        no_chdir => 1,
        wanted => sub {
            return unless -f $_ && /\.c\z/;
            return if /(?:^|\/)GK3R\.EXE\.c\z/;
            push @files, $_;
        },
    },
    $root
);

my $new_pattern = qr/\b\Q$new\E\b/;
for my $path (@files) {
    open my $file, '<', $path or die "cannot read $path: $!\n";
    local $/;
    my $contents = <$file>;
    close $file or die "cannot close $path: $!\n";
    $contents !~ $new_pattern
        or die "cannot rename: $new already exists in $path\n";
}

my $old_pattern = qr/\b\Q$old\E\b/;
my $total = 0;
for my $path (@files) {
    open my $file, '<', $path or die "cannot read $path: $!\n";
    local $/;
    my $contents = <$file>;
    close $file or die "cannot close $path: $!\n";

    my $count = $contents =~ s/$old_pattern/$new/g;
    next unless $count;

    open my $output, '>', $path or die "cannot write $path: $!\n";
    print {$output} $contents or die "cannot write $path: $!\n";
    close $output or die "cannot close $path: $!\n";
    $total += $count;
    print "$path: $count\n";
}

print "renamed $total occurrence(s)\n";
