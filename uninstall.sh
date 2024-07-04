#!/bin/bash

uninstall() {
	sudo rm -rf /usr/local/bin/zprobe-cli /usr/local/lib/libprober.so /usr/local/lib/libmemutils.so

}

uninstall_some() {
	sudo rm -rf /usr/local/lib/libprober.so /usr/local/lib/libmisc.so
}

if [ "$1" == "all" ]; then
	uninstall
elif [ "$1" == "libs" ]; then
	uninstall_some
else
	echo -e "\n[ERROR] Needs one argument\n\n\"all\"\n\"libs\""
fi
