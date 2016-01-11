 @echo off
 $current_dir_path=pwd
 echo $pwd
 
 while[ ${PWD##*/} != $"src"]
 do
 cp *.o ../
 rm *.o
 cd ..
 done
 cp *.o ../output/
 rm *.o
 cd ..
 cd $current_dir_path
 cd..