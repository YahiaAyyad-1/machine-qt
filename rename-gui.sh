#!/bin/bash

filename="$1"
newname="$2"
classname="$3"

[[ -z "$filename" || -z "$newname" || -z "$classname" ]] && {
	echo
	echo "Usage: rename-gui FILE-NAME NEW-NAME CLASS-NAME?"
	echo
	exit 1
}



exit 0

