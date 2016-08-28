# calc
A beautiful and robust calculator for the command line

## Dependencies
This calculator depends upon GNU readline library which is installed by default in
most *nix systems because bash also uses it.

## How to install?
Installation can be done easily by executing `./install.sh`.

Or can also be installed by the traditional `make` and `sudo make install` commands.

*Note: Default install location/prefix is `/usr/local/`. To change the location
use `make PREFIX=<dir> install`*

## Using man pages `if not installed`
- Viewing in terminal:

        groff -man -Tascii doc/man/man1/calc.1 | less

- Exporting as pdf:

        groff -man doc/man/man1/calc.1 | ps2pdf - > man_calc.pdf

- Exporting as html:

        groff -man -Thtml doc/man/man1/calc.1 > man_calc.html

*Note: The man page is generally updated after a long time. So, be careful with it.*

## I can't see it
This is a problem when the color of the input/output/error/prompt is nearly close
to that of the terminal's background color. This happens because, by default no
background is set when the calculator is first opened. The input color is by
default white so it would be problematic for people to see the input if they have
a background color close to white. To change the text color use:

`change input color black`

Similarly, output color can be changed using:

`change output color yellow`

For more information use `calc "help font" -q`.

## Your own configuration[init/rc file]
If you have finished fixing your colors then add the command(s) to a file lets say,
`/home/user/.calc.conf`. In turn make the calculator process the same file whenever
you open it using `calc -f /home/user/.calc.conf`. If that seems long to you then
add an alias to `.bashrc` lets say `calc_init` using
`alias calc_init='calc -f /home/user/.calc.conf'` command. After that just run
`calc_init` instead of `calc` to get your colors working without the need to change
colors every time you open the calculator.

Now that doesn't mean that it works only for colors. You can put in any direct
input command in `/home/user/.calc.conf` to (de)activate features of the calculator.
An example file is provided in the root of the repository named `.calc.config`. You
can modify it to suit your needs.
