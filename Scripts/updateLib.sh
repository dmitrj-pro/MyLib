#!/bin/bash

echo "\tFind Lib"

if [ -f conf.sh ];
then
	source conf.sh
fi

echo "\tRemove old files"
rm -rf ./*

if [ "$share" ];
then
	if [ "$Lib" ];
	then
		echo "Git address defined";
	else
		echo "Git address is not define";
		export Lib=../../git/lib.git;
	fi
	echo  "\tGit address is $Lib"
	
	echo  "\tClone Lib"
	git clone $Lib

	echo  "\tGenerate files"
	cd lib
	./init_example.sh init
else
	wget http://sr1.myprogram.us/dp/lib.tar.gz
	tar -xvf lib.tar.gz
	rm lib.tar.gz
	cd lib
fi

echo "\tRemove git files"
rm -rf ./.git/
rm -f ./init_example.sh

if [ "$share" ];
then 
	echo  "\tCreate archive"
	rm -f $share/lib.tar.gz
	rm -rf TEST
#	find . -name '*.*' | sort | xargs echo "{}\n"
	tar -zcvf $share/lib.tar.gz ../lib/*
	echo  "\tMove archive to $share"
fi;

echo  "\tBuilding lib"
make build

echo  "\tDelete cpp files"
make install_local

echo  "\tMove files to current folder"
mv ./* ../
cd ../

echo  "\tRemove tmp folder"
rm -rf lib

echo  "\tMove updateLib files"
mv ./Scripts/updateLib.sh ./

if [ "$share" ];
then 
	( echo "#!/bin/bash" && echo "export share=$share" && echo "export Lib=$Lib") > ./conf.sh;
	chmod +x ./conf.sh;
else
	echo "Not save config"
fi
