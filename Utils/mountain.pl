#!/usr/local/bin/perl
# -*-Perl-*-
# Last changed Time-stamp: <95/08/01 12:44:01 ivo>
# produce Pauline Hogeweg's mountain representation *_dp.ps files
# writes 2 sets of x y data separated by a "&"
# first set from partition function, second from mfe structure
# use e.g. as mountain.pl dot.ps | xmgr -pipe
# definition: mm[i],mp[i]=number of base pairs enclosing base i

while (<>) {
    chop;
    @F = split;
    if ($F[0] eq "/sequence") {
	$length = length($F[2])-2;
    }
    if ($F[3] eq "ubox") {
	$mp[$F[0]+1]+=$F[2]*$F[2]; # 
	$mp[$F[1]]-=$F[2]*$F[2];
    }
    if ($F[3] eq "lbox") {
	$mm[$F[0]+1]++;
	$mm[$F[1]]--;
    }
}
for ($i=1; $i<=$length; $i++) {
    $mp[$i]+=$mp[$i-1];
    $max = $mp[$i] if ($mp[$i]>$max);
    $mm[$i]+=$mm[$i-1];
    $max = $mp[$i] if ($mp[$i]>$max);    
}
for ($i=1; $i<=$length; $i++) {
    printf("%4d  %7.5g\n", $i, $mp[$i]);
}			
print "&\n";

for ($i=1; $i<=$length; $i++) {
    printf("%4d  %4d\n", $i, $mm[$i]);
}	
print "&\n";
