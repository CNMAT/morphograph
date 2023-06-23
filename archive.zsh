#!/bin/zsh

external_dir="externals"
xattr -dr $external_dir/morphograph.mxo

backup_dir="/Users/jml/Desktop/mgraph_patchers_backup"

echo "------------------------------"
echo "------------------------------"
echo "------------------------------"
echo " "
echo "back up dir is: " $backup_dir

if [ -d $backup_dir ]
then
	rm -rf $backup_dir/*
else
	mkdir $backup_dir
fi

echo " "
echo "------------syncing backup dir"
echo " "
#rsync -av --dry-run --exclude="build/*" --exclude ".git" --exclude="*.sh" $PWD $backup_dir
rsync -av --exclude="build/" --exclude ".git" --exclude="*.sh" $PWD/ $backup_dir

cp_dir="/Users/jml/Desktop/morphograph_alpha"

echo " "
echo "copy dir is: " $cp_dir

if [ -d $cp_dir ]
then
	rm -rf $cp_dir"/*"
else
	mkdir $cp_dir
fi

echo " "
echo "------------copying data to new desktop directory"
echo " "

cp -v help/morphograph.maxhelp docs/morphograph.maxref.xml $cp_dir
cp -R $external_dir/morphograph.mxo $cp_dir
cp -v help/*.wav $cp_dir
cp -v help/*.svg $cp_dir

echo " "
echo "------------archive complete.  Please see" $cp_dir "for details."
echo "------------backup dir is" $backup_dir

