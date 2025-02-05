#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/Bavafa/Desktop/CG-Lab2
  make -f /Users/Bavafa/Desktop/CG-Lab2/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/Bavafa/Desktop/CG-Lab2
  make -f /Users/Bavafa/Desktop/CG-Lab2/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/Bavafa/Desktop/CG-Lab2
  make -f /Users/Bavafa/Desktop/CG-Lab2/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/Bavafa/Desktop/CG-Lab2
  make -f /Users/Bavafa/Desktop/CG-Lab2/CMakeScripts/ReRunCMake.make
fi

