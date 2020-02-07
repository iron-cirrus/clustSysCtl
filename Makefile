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
	sudo cp startHeadCluster /etc/init.d
	sudo cp startHeadCluster64 /var/lib/machines/debian-stretch-64/etc/init.d
	sudo cp startNode /nfs/client1/etc/init.d
	sudo cp startNode /nfs/client1/var/lib/machines/debian-stretch-64/etc/init.d
FORCE:
