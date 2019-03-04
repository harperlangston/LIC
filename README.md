# LIC
Line Integral Convolution Code based on the work of Cabral and Leedom: http://cs.brown.edu/courses/csci2370/2000/1999/cabral.pdf

Some old results: http://harperlangston.com/stokes/


DESCRIPTION:

There are two programs here:  rand and main.  By default,
make makes main which runs the LIC.  PLus, there's a
script to convert to ppm for mpeg encoding.
I'll describe the rand program first however 
(type make rand to create):

1.  ./rand <options>
	
	rand generates the n x m random noise image file,
	rand.pgm and the corresponding data file, rand.dat
	that can be taken as data for "main" (see below).
	rand.dat and rand .pgm by default is 100 x 100.  To
	make them different sizes, use the options, -H Num1
	and -W Num2.  For example:

		./rand -H 100 -W 400
	
	makes rand.dat and rand.pgm of height 100 and width 
	400.  It's important that rand.dat is the same size 
	as your input velocity field.

2.  /.main <options>
	
	(type make or make main to create)

	main takes a velocity field and input image and outputs 
	a convoluted image according to LIC.  The velocity file 
	should be of the following format:

	ux_0 uy_0 uz_0 . . . ux_end uy_end uz_end

	I currently have the velocities at each point on different lines.
	That is:

	ux_0 uy_o uz_0
	.
	.
	.
	ux_end uy_end uz_end

	but it shouldn't matter if you do it consecutively.
	Also, (ux_0, uy_0, uz_0) is the bottom left hand point's
	velocity and then the field is arranged to go to the right
	and then up to the next line such that (ux_end, uy_end, uz_end)
	is the top right point.  If the data is different, you may have 
	to flip the image accordingly either manually or in the code.

	The options for ./main are:

	-W Num : gives the width of the input velocity field and image
	-H Num : gives height (W and H default to 100 I believe)
	-in File : gives input image data of size H x W (defaults to rand.dat)
                   make sure this is a pure .dat file, no pgm headers
	-out File : Name of the output pgm file.  (defaults to either out.dat
	            or out.pgm)
	-vel File : Name of input velocity field of size H x W ( x 3 for each
	            of ux, uy and uz).  Deafults to velocity.dat
	-L Num : Filterlength to be used.  Defaults to 15.  Play with
	         this sum.  Too short and nothing happens.  Too long and
	         output image looks horrible.  10 -20 seems pretty good.

	You can also play with the convolution coefficients in LIC which
	I'm going to allow to be changed from the command line since
	different coefficients seem to work for different velocity fields.

3. process_ppm file

	file is a pgm file which is turned into a ppm file
	using pgmtoppm and pnmdepth mostly, so make sure
	those scripts are on your machine.  In the line:
	pgmtoppm rgbi: xx/xx/xx, each xx is an rgb value between
	0 and 1 (float), so change that according to desired color.
	You can use mpeg2encode for movie making.
	See http://tns-www.lcs.mit.edu/manuals/mpeg2/
 	for information.



	
	
