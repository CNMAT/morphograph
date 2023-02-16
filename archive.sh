#!/bin/bash

external_dir=~/Documents/Max\ 8/Packages/max-sdk/externals
xattr -dr "$external_dir"/morphograph.mxo

backup_dir=../mgraph_patchers_backup

if [[ -d $backup_dir ]] 
then
	rm -rf $backup_dir/*
else
	mkdir $backup_dir
fi

echo " "
echo "------------syncing backup dir"
echo " "
rsync -av --exclude=*.sh ./ $backup_dir

cp_dir=~/Desktop/morphograph_alpha

if [[ ! -d $cp_dir ]]
then
	mkdir $cp_dir
fi

echo " "
echo "------------copying data to desktop directory"
echo " "
rm -rf $cp_dir/*
cp -v morphograph.maxhelp morphograph.maxref.xml $cp_dir
cp -R "$external_dir"/morphograph.mxo $cp_dir
cp -v *.wav $cp_dir
cp -v *.svg $cp_dir
cp -vR svg_tests $cp_dir

echo " "
echo "------------archive complete.  Please see" $cp_dir "for details."
echo "------------backup dir is" $backup_dir

