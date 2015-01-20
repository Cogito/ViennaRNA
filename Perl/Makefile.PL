# File : Makefile.PL
use ExtUtils::MakeMaker;
WriteMakefile(
	NAME	=>	"RNA",
	LIBS	=>	["-lm"],
	OBJECT  =>	"RNA_wrap.o ../lib/libRNA.a"
);
