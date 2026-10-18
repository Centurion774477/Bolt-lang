import sys
import frontendb as front
import vmb as vm
import backendb as backend
import lang

if sys.argv[1] == "frontend":
    front.build()
elif sys.argv[1] == "vm":
    vm.build()
elif sys.argv[1] == "backend":
    backend.build()
elif sys.argv[1] == "lang":
    lang.build()