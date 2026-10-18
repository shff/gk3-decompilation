#!/usr/bin/perl

use strict;
use warnings;
use File::Find;
use File::Basename qw(dirname);
use File::Spec;

@ARGV == 1 or die "usage: $0 FUNCTION_NAME\n";
my ($name) = @ARGV;
$name =~ /\A[A-Za-z_][A-Za-z_0-9]*\z/
    or die "invalid C function name: $name\n";

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

my $found = 0;
for my $path (sort @files) {
    open my $file, '<', $path or die "cannot read $path: $!\n";
    local $/;
    my $source = <$file>;
    close $file or die "cannot close $path: $!\n";

    while ($source =~ /\b\Q$name\E\s*\(/g) {
        my $name_start = $-[0];
        my $open_paren = index($source, '(', $name_start);
        my $close_paren = matching_delimiter($source, $open_paren, '(', ')');
        next unless defined $close_paren;

        my $after_parameters = skip_space_and_comments($source, $close_paren + 1);
        next unless substr($source, $after_parameters, 1) eq '{';

        my $body_end = matching_delimiter($source, $after_parameters, '{', '}');
        next unless defined $body_end;

        my $definition_start = $name_start;
        $definition_start-- while $definition_start > 0
            && substr($source, $definition_start - 1, 1) =~ /[A-Za-z_0-9]/;
        while ($definition_start > 0
            && substr($source, $definition_start - 1, 1) =~ /[ \t]/) {
            --$definition_start;
        }
        while ($definition_start > 0
            && substr($source, $definition_start - 1, 1) !~ /[;{}\n]/) {
            --$definition_start;
        }
        $definition_start++ if substr($source, $definition_start, 1) eq "\n";

        my $line = 1 + (substr($source, 0, $name_start) =~ tr/\n//);
        my $definition = substr($source, $definition_start, $body_end - $definition_start + 1);
        my $relative_path = File::Spec->abs2rel($path, $root);
        print "=== $relative_path:$line ===\n$definition\n\n";
        $found = 1;
        pos($source) = $body_end + 1;
    }
}

if (!$found) {
    print "No function definition found for $name\n";
    exit 1;
}

sub skip_space_and_comments {
    my ($text, $position) = @_;
    my $length = length $text;

    while ($position < $length) {
        my $tail = substr($text, $position);
        if ($tail =~ /\A\s+/) {
            $position += length $&;
        } elsif ($tail =~ m{\A/\*}) {
            my $end = index($text, '*/', $position + 2);
            return $length if $end < 0;
            $position = $end + 2;
        } elsif ($tail =~ m{\A//}) {
            my $end = index($text, "\n", $position + 2);
            return $length if $end < 0;
            $position = $end + 1;
        } else {
            last;
        }
    }

    return $position;
}

sub matching_delimiter {
    my ($text, $start, $open, $close) = @_;
    my $depth = 0;
    my $state = 'code';
    my $length = length $text;

    for (my $i = $start; $i < $length; ++$i) {
        my $char = substr($text, $i, 1);
        my $next = $i + 1 < $length ? substr($text, $i + 1, 1) : '';

        if ($state eq 'line_comment') {
            $state = 'code' if $char eq "\n";
        } elsif ($state eq 'block_comment') {
            if ($char eq '*' && $next eq '/') {
                $state = 'code';
                ++$i;
            }
        } elsif ($state eq 'string' || $state eq 'character') {
            if ($char eq '\\') {
                ++$i;
            } elsif (($state eq 'string' && $char eq '"')
                || ($state eq 'character' && $char eq "'")) {
                $state = 'code';
            }
        } elsif ($char eq '/' && $next eq '/') {
            $state = 'line_comment';
            ++$i;
        } elsif ($char eq '/' && $next eq '*') {
            $state = 'block_comment';
            ++$i;
        } elsif ($char eq '"') {
            $state = 'string';
        } elsif ($char eq "'") {
            $state = 'character';
        } elsif ($char eq $open) {
            ++$depth;
        } elsif ($char eq $close) {
            --$depth;
            return $i if $depth == 0;
        }
    }

    return undef;
}
