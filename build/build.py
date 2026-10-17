import sys
import frontendb as front
import vmb as vm

if (sys.argv[1] == "frontend"):
    front.build()
elif (sys.argv[1] == "vm"):
    vm.build()