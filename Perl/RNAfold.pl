#!/usr/local/bin/perl
# -*-Perl-*-
# Last changed Time-stamp: <97/11/25 19:20:33 ivo>

use RNA;
use Getopt::Long;

 Getopt::Long::config(no_ignore_case);

$scale = "....,....1....,....2....,....3....,....4" .
    "....,....5....,....6....,....7....,....8";


&usage() unless GetOptions("p" => \$pf,
			   "p1" => \$pf,
			   "p0" => \$pf0,
			   "C"   => \$RNA::fold_constrained,
			   "T=f" => \$RNA::temperature,
			   "4", "d", "d2", "d3",
			   "noGU" => \$RNA::noGU,
			   "noCloseGU" => \$RNA::no_closingGU,
			   "noLP" => \$RNA::noLonelyPairs,
			   "e=i" => \$RNA::energy_set,
			   "P=s" => \$ParamFile,
			   "nsp=s" => \$ns_bases,
			   "S=f" => \$sfact);

if ($pf0) {
  $RNA::backtrack=0;
  $pf=1;
}
$RNA::tetra_loop = 0 if ($opt_4);
$RNA::dangles = 0 if ($opt_d);
$RNA::dangles = 2 if ($opt_d2);
$RNA::dangles = 3 if ($opt_d3);

 RNA::read_parameter_file($ParamFile) if ($ParamFile);

if ($ns_bases) {
    $RNA::nonstandards = "";
    foreach $p ( split(/,/, $ns_bases) ) {
	if ($p =~ s/^-//) {
	    $RNA::nonstandards .= reverse($p)
	    }
	$RNA::nonstandards .= $p;
    }
    print "$RNA::nonstandards\n";
}

$istty = (-t STDIN) && (-t STDOUT);
if (($RNA::fold_constrained)&&($istty)) {
    print "Input constraints using the following notation:\n";
    print "| : paired with another base\n";
    print ". : no constraint at all\n";
    print "x : base must not pair\n";
    print "< : base i is paired with a base j<i\n";
    print "> : base i is paired with a base j>i\n";
    print "matching brackets ( ): base i pairs base j\n";
} 
	
if ($istty) {
    print "\nInput string (upper or lower case); @ to quit\n";
    print "$scale\n";
}
while (<>) {	# main loop: continue until end of file 
    $fname="";
    
    # skip comment lines and get filenames
    if (/^>\s*(\S+)/) {
	$fname = $1;
	next;
    }

    last if (/^@/);

    if (/(\S+)/) {
	$string = $1;
    } else {
	next;
    }
    
    $string = uc($string);
    $length = length($string);
    printf("length = %d\n", $length) if ($istty);

    if ($RNA::fold_constrained) {
	$_ = <>;
	$cstruc = $1 if (/(\S+)/);
	die("constraint string has wrong length")
	    if (length($cstruc)!=$length);
	$structure = $cstruc;
    } else {
	$structure = $string; # wierd way to allocate space
    }
    $min_en = RNA::fold($string, $structure);
    print "$string\n$structure";
    if ($istty) {
	printf("\n minimum free energy = %6.2f kcal/mol\n", $min_en);
    } else {
	printf(" (%6.2f)\n", $min_en);
    }
    if (length($fname)>0) {
	$ffname = $fname . "_ss.ps";
      } else {
	  $ffname = "rna.ps";
      }
      RNA::PS_rna_plot($string, $structure, $ffname);

    if ($pf) {

	# recompute with dangles as in pf_fold()
	$RNA::dangles=2 if ($RNA::dangles);
	$min_en = RNA::energy_of_struct($string, $structure); 
	
	$kT = ($RNA::temperature+273.15)*1.98717/1000.; # in Kcal 
	$pf_scale = exp(-($sfact*$min_en)/$kT/$length);
	print STDERR "scaling factor $pf_scale\n" if ($length>2000);

	$structure = $cstruc if ($RNA::fold_constrained);
	$energy = RNA::pf_fold($string, $structure);
	 
	if ($RNA::do_backtrack) {
	    print $structure;
	    printf(" [%6.2f]\n", $energy) if (!$istty);
	    print "\n";
	}
	if (($istty)||(!$RNA::do_backtrack)) {
	    printf(" free energy of ensemble = %6.2f kcal/mol\n", $energy);
	    printf(" frequency of mfe structure in ensemble %g\n",
		   exp(($energy-$min_en)/$kT));
	}
	
	if ($RNA::do_backtrack) {
	    $ffname = ($fname)?($fname . "_dp.ps"):"dot.ps";
	  RNA::PS_dot_plot($string, $ffname);
	}
    }
} 

 RNA::free_pf_arrays() if ($pf);
 RNA::free_arrays();
 RNA::write_parameter_file("test.par");

sub usage()
{
    die("usage: " . 
	"RNAfold [-p[0]] [-C] [-T temp] [-4] [-d] [-noGU] [-noCloseGU]\n" .
	"               [-e e_set] [-P paramfile] [-nsp pairs] [-S scale]");
}


# End of file
