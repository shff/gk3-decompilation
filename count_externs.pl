#!/usr/bin/perl

use strict;
use warnings;
use File::Find;
use File::Basename qw(dirname);
use File::Spec;

my $root = dirname(File::Spec->rel2abs($0));
my @files;
find(
    {
        no_chdir => 1,
        wanted => sub {
            return unless -f $_ && /\.c\z/;
            return if /(?:^|\/)[^\/]*_rest\.c\z/;
            push @files, $_;
        },
    },
    $root
);
@files = sort @files;

my %definitions;
for my $path (@files) {
    add_function_definitions(read_file($path), \%definitions);
}

my @counts;
for my $path (@files) {
    my @externs = find_extern_function_declarations(read_file($path));
    my %seen;
    my @matches = sort grep { !$seen{$_}++ && !$definitions{$_} } @externs;
    push @counts, [scalar(@matches), $path, \@matches];
}

@counts = sort { $b->[0] <=> $a->[0] || $a->[1] cmp $b->[1] } @counts;
print "externs without definitions outside *_rest.c\tfile\tfunction names\n";
for my $entry (@counts) {
    my ($count, $path, $names) = @$entry;
    my $relative_path = File::Spec->abs2rel($path, $root);
    print "$count\t$relative_path\t", join(', ', @$names), "\n";
}

sub read_file {
    my ($path) = @_;
    open my $file, '<', $path or die "cannot read $path: $!\n";
    local $/;
    my $contents = <$file>;
    close $file or die "cannot close $path: $!\n";
    return $contents;
}

sub find_extern_function_declarations {
    my ($source) = @_;
    my $code = mask_non_code($source);
    my @names;

    while ($code =~ /\bextern\b([^;]*);/g) {
        my $declaration = $1;
        next if $declaration =~ /\(\s*(?:__[A-Za-z_][A-Za-z_0-9]*\s+)*\*/;
        my @declarators = $declaration =~ /\b([A-Za-z_][A-Za-z_0-9]*)\s*\(/g;
        push @names, $declarators[0] if @declarators;
    }

    return @names;
}

sub add_function_definitions {
    my ($source, $definitions) = @_;
    my $code = mask_non_code($source);
    my $statement = '';
    my $depth = 0;
    my $last_position = 0;

    while ($code =~ /[{};]/g) {
        my $token = $&;
        my $token_start = $-[0];
        my $between = substr($code, $last_position, $token_start - $last_position);

        if ($depth == 0) {
            $statement .= $between;
            if ($token eq ';') {
                $statement = '';
            } elsif ($token eq '{') {
                if ($statement !~ /=/) {
                    my @candidates = $statement =~ /\b([A-Za-z_][A-Za-z_0-9]*)\s*\([^;]*\)\s*\z/s;
                    $definitions->{$candidates[-1]} = 1 if @candidates;
                }
                $statement = '';
                $depth = 1;
            }
        } elsif ($token eq '{') {
            ++$depth;
        } elsif ($token eq '}') {
            --$depth;
            $statement = '' if $depth == 0;
        }

        $last_position = $+[0];
    }
}

sub mask_non_code {
    my ($source) = @_;
    $source =~ s{
        (/\* .*? \*/)
        | (// [^\n]*)
        | (" (?: \\. | [^"\\] )* ")
        | ('  (?: \\. | [^'\\] )* ')
    }{
        my $token = $&;
        $token =~ s/[^\n]/ /g;
        $token;
    }gsex;
    return $source;
}
