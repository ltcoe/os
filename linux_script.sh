#!bin/sh
echo "__________"
echo "OS Info"
cat /etc/os-release
uname -r
uname -a
uname -v
echo "__________"
echo "10 processes in descending order"
ps -eo pid,ppid,cmd,%mem,%cpu --sort=%mem|head -
10
echo "__________"
echo "Highest memory usage"
ps -eo pid,ppid,cmd,%mem,%cpu --sort=%mem|head -2
echo "__________"
echo "user login and name"
whoami
logname
echo "$SHELL"
pwd
uname -srm
echo "__________"
