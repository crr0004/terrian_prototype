#!/bin/bash
if [[ -e "./Terrian.bin" ]]
then
	rm "./Terrian.bin"
fi
scons debug=3
