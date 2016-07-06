#ifndef CALC_TERM_CSI_H
#define CALC_TERM_CSI_H

#ifndef CSI         /* if CSI is already defined during compilation */
# define CSI "\033["/* do not define it again */
#endif

#define /* Cursor Up */               CSICUU CSI"A"
#define /* Cursor Down */             CSICUD CSI"B"
#define /* Cursor Forward */          CSICUF CSI"C"
#define /* Cursor Backward */         CSICUB CSI"D"
#define /* Cursor Next Line */        CSICNL CSI"E"
#define /* Cursor Previous Line */    CSICPL CSI"F"
#define /* Cursor Col Absolute */     CSICHA CSI"G"
#define /* Cursor Position */         CSICUP CSI";H"
#define /* Erase Display */           CSIED  CSI"J"
#define /* Erase Line */              CSIEL  CSI"K"
#define /* Save Cursor Position */    CSISCP CSI"s"
#define /* Restore Cursor Position */ CSIRCP CSI"u"
#define /* Device Status Report */    CSIDSR CSI"6n"
#define /* Scroll Up */               CSISU  CSI"S"
#define /* Scroll Down */             CSISD  CSI"T"

/* formated versions for variable values used by printf */
#define FCSICUU CSI"%dA"
#define FCSICUD CSI"%dB"
#define FCSICUF CSI"%dC"
#define FCSICUB CSI"%dD"
#define FCSICNL CSI"%dE"
#define FCSICPL CSI"%dF"
#define FCSICHA CSI"%dG"
#define FCSICUP CSI"%d;%dH"
#define FCSIED  CSI"%dJ"
#define FCSIEL  CSI"%dK"
#define FCSISU  CSI"%dS"
#define FSCISD  CSI"%dT"

#define AFTER  0 /* Erase after  something */
#define BEFORE 1 /* Erase before something */
#define FULL   2 /* Fully erase  the thing */

#endif
