#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/Bavafa/Desktop/Lab_Skeleton
  make -f /Users/Bavafa/Desktop/Lab_Skeleton/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/Bavafa/Desktop/Lab_Skeleton
  make -f /Users/Bavafa/Desktop/Lab_Skeleton/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/Bavafa/Desktop/Lab_Skeleton
  make -f /Users/Bavafa/Desktop/Lab_Skeleton/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/Bavafa/Desktop/Lab_Skeleton
  make -f /Users/Bavafa/Desktop/Lab_Skeleton/CMakeScripts/ReRunCMake.make
fi

