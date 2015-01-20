#!/usr/local/bin/perl -w
# -*-Perl-*-
# Last changed Time-stamp: <1998-06-24 17:32:47 ivo>

require 5.004;

use Tk::Canvas;

use strict;

$, = ' ';
#some global variables
my $size = 600;    # initial size of dot plot canvas
my $ssize = $size; # size of scrollregion
my $magstep = 0;   # zoomfactor
my $length;        # sequence length
my $scalef;        # scaling factor (depends on size, magstep and length)
my $minread = 0.03;  # read entries from dot plot with p>0.03
my $o_minp = 10;   # draw_boxes draws everything with p<o_minp

my $main = new MainWindow;
# main window
$main->title("Ivo's Tk Dot Plot Viewer");

# frame for buttons and controls
my $cframe = $main->Frame;
$cframe->pack(-fill => 'x');
$cframe->Button(-text => 'Quit',
	      -command => sub{exit}
	      )->pack(-side => 'right');
$cframe->Button(-text => 'Redraw',
	      -command => sub{
		  $o_minp = 10;
		  &draw_boxes;
	      }
	      )->pack(-side => 'right');

# field to display info on current pair
my $CurrentPair="";
my $Info_field = $cframe->Message(qw/-width 10c -textvariable/
				=> \$CurrentPair);
$Info_field->pack(qw/-side left/);

# canvas for dot plot
my $canvas = $main->Scrolled(qw/Canvas -relief sunken -borderwidth 2
			     -scrollbars se -width/ => $size, -height => $size,
			     -scrollregion => [0,0,$ssize, $ssize],
			     -background => 'white');
$canvas->pack(-expand => 'yes',  -fill => 'both', -padx => 1, -pady =>1);

print times, "\n";
print STDERR "reading dot plot...";
my (%ubox, %lbox, $seq);  # filled in by read_dot_plot
&read_dot_plot(); 
print "\n";
print times, "\n";

$length = length($seq);
$scalef = $size/($length);
my $minp = 1/(10*$scalef);    # squares with p<minp are not drawn
print $minp, "\n";
$minp = 0.8 if ($minp>0.8);



$canvas->createLine(0,0,$ssize,$ssize);
&draw_boxes;

$main->update();

my $margin = $canvas->Width - $size;  # $canvas->Width includes scrollbars

&add_bindings;
print times, "\n";

Tk::MainLoop;

# end of main

sub read_dot_plot {
    # first get the sequence
    while (<>) {  
	next unless (/\/sequence \{ \((\S*)[\\\)]/);
	$seq = $1;              # empty for new version
	while (!/\) \} def/) {  # read until end of definition
	    $_ = <>;
	    /(\S*)[\\\)]/;      # ends either with `)' or `\' 
	    $seq .= $1;
	}
	last;
    }
    # read on for pairs
    while (<>) {
	next unless (/.box$/);
	my($i, $j, $p, $id) = split;
	next unless ($p>$minread);  
	$ubox{$i,$j} = $p if ($id eq "ubox");
	$lbox{$i,$j} = $p if ($id eq "lbox");
    }
}

sub draw_boxes {
    my $pp;
    my $orig_cursor = ($main->configure(-cursor))[3];
    $main->configure(-cursor => 'watch');
    $main->update();
    print STDERR "drawing boxes...";
    $canvas->delete('all');
    $canvas->createLine(0,0,$ssize,$ssize);

    foreach $pp (keys %ubox) {
	my ($i,$j) = split($;,$pp);
	my $p = $ubox{$pp};
	# draw anything with minp<p<o_minp
	make_box($j, $i, $p) if ($p>=$minp);
    }
    foreach $pp (keys %lbox) {
	my ($i,$j) = split($;,$pp);
	my $p = $lbox{$pp};
	make_box($i, $j, $p) if ($p>=$minp);
    }
    $main->configure(-cursor => $orig_cursor);
    $o_minp = $minp;
    print STDERR "\n";
    print times, "\n";
}

sub make_box {
    my ($i, $j, $p) = @_;
    my $pp = $p*$scalef;

    my $x1 = ($i-0.5-$p/2)*$scalef;  # centered between i and i+1
    my $y1 = ($j-0.5-$p/2)*$scalef;
    my $c = '#000';
    if ($pp<0.7) {   # grayscale aliasing for small rectangles
	$c = (0.7-$pp)*21;  # map to [0..15]
	$c = (0 .. 9, 'a' .. 'f')[$c & 15];
	$c = "#$c$c$c";
    }
    $canvas->createRectangle($x1,  $y1, $x1+$pp, $y1+$pp,
			     -fill => $c, -outline => undef);
}

sub add_bindings {
    # display pair info
#    $canvas->bind('all', '<Enter>' => sub {
#	my($c) = @_;
#	my $id = $c->find('withtag' => 'current');
#	my @taglist = $canvas->gettags($id);
#	$CurrentPair = shift @taglist;
#    });
    # or better...
    $canvas->CanvasBind('<Motion>' => sub {
	my $c = shift;
	my $e = $c->XEvent;
	my $x = $canvas->canvasx($e->x);
	$x = int($x/$scalef +1);
	my $y = $canvas->canvasy($e->y);
	$y = int($y/$scalef +1);
	$CurrentPair = "$y,$x";
    });
    # button 2 scrolls
    my ($scanX, $scanY);
    $canvas->CanvasBind('<2>' => sub {
	my $c = shift;
	my $e = $c->XEvent;
	$scanX = $e->x; $scanY = $e->y;
	$c->scan('mark', $e->x, $e->y);
    });
    $canvas->CanvasBind('<B2-Motion>' => sub {
	my $c = shift;
	my $e = $c->XEvent;
	my $x = $scanX + ($e->x -$scanX)/10;
	my $y = $scanY + ($e->y -$scanY)/10;
	$c->scan('dragto', $x, $y);
#	$canvas->xview(scroll => $e->x - $scanX, 'unit');
#	$canvas->yview(scroll => $e->y - $scanY, 'unit');
    });
    
    $canvas->CanvasBind('<1>' => sub {
	my $c = shift;
#	my $e = $c->XEvent;
#	print $e->x, ' ', $e->y, "\n";
	my ($i, $j) = split(/,/,$CurrentPair);
	if ($i>$j) {
	    my $ii = $i;
	    $i =$j; $j=$ii;
	}
	$CurrentPair = "$i,$j " . substr($seq,$i-1,1) . substr($seq,$j-1,1);
	$CurrentPair .= " p=$ubox{$i,$j}" if (exists $ubox{$i,$j});
    });

    # rescale everything if window is resized
    $canvas->CanvasBind('<Configure>' => sub {
	my $new_size = $canvas->Width;
	$new_size = $canvas->Height if ($canvas->Height<$new_size);
	$new_size -= $margin;
	if ($new_size>$ssize) {
	    my $rscale = $new_size/$ssize;
	    $canvas->scale('all', 0, 0, $rscale, $rscale);
	    $scalef *= $rscale;
	    $size  = $ssize = $new_size;
	    $canvas->configure(-scrollregion => [0,0,$ssize, $ssize]);
	} else {
	    $size = $new_size;
	}
    });
    
    # zoom in and out
    $main->bind('<plus>' => \&zoom_in);
    $main->bind('<KP_Add>' => \&zoom_in);
    $main->bind('<minus>' => \&zoom_out);
    $main->bind('<KP_Subtract>' => \&zoom_out);
}

sub zoom_in {
    $scalef *= 1.2;
    $ssize *= 1.2;
    my ($x1, $x2) = $canvas->xview;
    my ($y1, $y2) = $canvas->yview;
    $canvas->configure(-scrollregion => [0,0,$ssize, $ssize]);
    $canvas->xview(moveto => $x1+($x2-$x1)*0.1);
    $canvas->yview(moveto => $y1+($y2-$y1)*0.1);
    $canvas->scale('all', 0, 0, 1.2, 1.2);

    $minp = 1/(10*$scalef);
    $minp = 0.8 if ($minp>0.8);
    &draw_boxes if ((3*$minp<$o_minp)&&($o_minp>$minread));
}

sub zoom_out {
    my $f = 1/1.2;
    $f = $size/$ssize if ($ssize*$f < $size); # keep $ssize>=$size
    $ssize *= $f;
    $scalef *= $f;
    my ($x1, $x2) = $canvas->xview;
    my ($y1, $y2) = $canvas->yview;
    $canvas->configure(-scrollregion => [0,0,$ssize, $ssize]);
    my $ff = ($f-1)/2;
    $canvas->xview(moveto => $x1+($x2-$x1)*$ff);
    $canvas->yview(moveto => $y1+($y2-$y1)*$ff);
    $canvas->scale('all', 0, 0, $f, $f);
    
    $minp = 1/(10*$scalef);
    $minp = 0.8 if ($minp>0.8);   # always draw squres with p>0.8

    &draw_boxes if ($minp>3*$o_minp);;
}

# End of file
