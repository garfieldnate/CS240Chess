#CS 240 Chess

This is a chess game created for an assignment in CS 240 at BYU in 2011. The purpose of the class was to 1) teach us how to work with "large" codebases and 2) introduce us to Linux, C++ and Makefiles. The class was famous for its "nightmare" projects among CS majors, but it was actually a lot of fun. The thing I remember most from the class is that C/C++ are a pain in the butt to work with :).

The class has since changed and the assignment no longer exists. I am storing this mostly for historical significance.

The original specification can be found [here](https://faculty.cs.byu.edu/~rodham/cs240/chess/). For this project we were given a GUI and had to construct the model and controller for a chess game. AI was extra credit, so this program just takes random moves for the computer's turn, but the game does determine legal moves and detect check and checkmate.

##Building/Running
As-is, this project can only be compiled and run on a Posix platform.

To build/run unit tests:

    make test
    bin/testchess

To build/run the full game, you first need to install Glade, which is used for the GUI. The required packages are lib-gtkmm-2.4-dev and lib-glademm-2.4-dev. Then run:

    make bin
    bin/chess h c # h for human, c for computer (the AI is dumb)

To back up your work you can run `make backup` to generate a tarball named with today's date. I think I was barely learning SVN near the end of this class...

##Checking Memory
A suppression file is included which suppresses `valgrind` warnings caused by the standard string library. To run the tests or game with memory checking on, use:

    make mchecktest
    make mcheckgui

##Author
Nathan Glenn, 2011
