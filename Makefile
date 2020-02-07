SHELL:=/bin/bash

all:FORCE
	echo global deployment
	#shellcheck clustSysCtl > clustSysCtl.check
	# Nous sommes sur une machine 64 
	# les start de la machine 32 et 64 ne font pasz les meme choses 
	# car l'hote rend ces ressources transprente sur la machine virtuelle 64
	sudo cp clustSysCtl /usr/bin
	sudo cp mssh /usr/bin
	sudo cp mcmd /usr/bin
	#startup de la machine router 
	sudo cp startHeadCluster64 /etc/init.d
	
	#Maj des cmd client / Node 
	ssh 127.0.0.1 sudo cp /home/pi/projets/clustSys/startNode /nfs/client1/etc/init.d
	ssh 127.0.0.1 sudo cp /home/pi/projets/clustSys/startNode64 /nfs/client1/var/lib/machines/debian-stretch-64/etc/init.d
	
	# install sur l'hote 32 bits aussi
	ssh 127.0.0.1 sudo cp /home/pi/projets/clustSys/clustSysCtl /usr/bin
	ssh 127.0.0.1 sudo cp /home/pi/projets/clustSys/mssh /usr/bin
	ssh 127.0.0.1 sudo cp /home/pi/projets/clustSys/mcmd /usr/bin
	ssh 127.0.0.1 sudo cp /home/pi/projets/clustSys/startHeadCluster /etc/init.d
	
#mssh:FORCE
	#shellcheck mssh > mssh.check
	
#mcmd:FORCE
	#shellcheck mcmd > mcmd.check
	
	
FORCE:
