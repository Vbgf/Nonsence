#!/bin/bash
echo "Automated git update sript:"
cd ~/Desktop/Nonsence
echo "Nonsence:"
git pull
cd ../software_engineering_2014
echo "software_engineering_2014:"
git pull
cd ../lazy_slobs
echo "lazy_slobs:"
git pull
cd ../teach2014-2015
echo "teach2014-2015:"
git pull
cd ../pps
echo "pps:"
git pull
clear
