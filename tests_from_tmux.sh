#~/bin/bash
if [[ -e "./Tests_Terrian.bin" ]]
then
	rm "./Tests_Terrian.bin"
fi
scons debug=3 --tests
