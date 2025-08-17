#!/bin/bash

set -e
rm -rf *.user*

cwd=$(pwd)
sources=control-qt-1.1.0
tar_file=control-qt-1.1.0.tar.gz
pro_file=SOURCES/control-qt-1.1.0/Qt-Client.pro
spec_file=SPECS/control-qt-1.1.0.spec
rpm_file=RPMS/$(arch)/control-qt-1.0-0.el7.$(arch).rpm
rpm_repo=~/nfs/groups/control/rpm-repo

mkdir -p ~/rpmbuild/SOURCES/control-qt-1.1.0
cp -va * ~/rpmbuild/SOURCES/control-qt-1.1.0
cd ~/rpmbuild
sed -i '11d;' $pro_file
sed -i '13i\\n' $pro_file
sed -i '14iclient.path = /usr/bin' $pro_file
sed -i '15iclient.files = Qt-Client' $pro_file
sed -i '16iINSTALLS += client' $pro_file
sed -i '17d;' $pro_file

epoch=$(grep -E ^Epoch $spec_file | awk '{print $2}')
epoch=$((epoch+1))
sed -i "11s/^Epoch:.*/Epoch:\t\t\t$epoch/" $spec_file

cd SOURCES
tar czvf $tar_file $sources
cd -

rpmbuild -ba $spec_file
./publish-rpms.sh control-qt locally-developed

cd $cwd
