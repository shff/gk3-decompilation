#!/usr/bin/perl

use strict;
use warnings;
use File::Find;
use File::Basename qw(dirname);
use File::Spec;

my $root = dirname(File::Spec->rel2abs($0));
my $pattern = qr/\b(?:sub|loc|off|byte|word|dword|qword|xmmword|ymmword|zmmword|tbyte|oword|unk|asc|stru|flt|dbl|real|nullsub|j)_[0-9A-Fa-f]+\b/;
my @counts;

find(
    {
        no_chdir => 1,
        wanted => sub {
            return unless -f $_ && /\.c\z/;
            return if /(?:^|\/)[^\/]*_rest\.c\z/;
            return if /(?:^|\/)GK3R\.EXE\.c\z/;

            open my $file, '<', $_ or die "cannot read $_: $!\n";
            local $/;
            my $contents = <$file>;
            close $file or die "cannot close $_: $!\n";

            my (%by_identifier, %by_prefix);
            while ($contents =~ /$pattern/g) {
                my $identifier = $&;
                next if $by_identifier{$identifier}++;
                my ($prefix) = $identifier =~ /\A([A-Za-z]+)_/;
                ++$by_prefix{$prefix};
            }

            my $total = 0;
            $total += $_ for values %by_prefix;
            push @counts, [$total, $_, \%by_prefix];
        },
    },
    $root
);

@counts = sort { $b->[0] <=> $a->[0] || $a->[1] cmp $b->[1] } @counts;
print "identifiers\tfile\tprefix breakdown\n";
for my $entry (@counts) {
    my ($total, $path, $by_prefix) = @$entry;
    my $relative_path = File::Spec->abs2rel($path, $root);
    my $breakdown = join ', ', map { "$_=$by_prefix->{$_}" }
        sort keys %$by_prefix;
    print "$total\t$relative_path\t$breakdown\n";
}
