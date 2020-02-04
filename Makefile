SHELL:=/bin/bash
all:FORCE
	#shellcheck clustSysCtl > clustSysCtl.check
	sudo cp clustSysCtl /usr/bin
#mssh:FORCE
	#shellcheck mssh > mssh.check
	sudo cp mssh /usr/bin
#mcmd:FORCE
	#shellcheck mcmd > mcmd.check
	sudo cp mcmd /usr/bin

FORCE:
