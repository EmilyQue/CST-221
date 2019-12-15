#!/bin/bash

#sets file and group names
filename="users.txt"
group="testGroup"

#checks if group already exists
if grep -q $group /etc/group
then 
	echo "$group already exists."
#creates new group
else 
	groupadd $group
fi

#reads username and password from file
filename="users.txt"
while read -r username password
do 
	name="$username"
	pswrd="$password"
	echo "Username: $name"
	echo "Password: $pswrd"
#adds user to group
	if [ $(id -u) -eq 0 ]; then
		egrep "^$name" /etc/passwd >/dev/null
		if [ $? -eq 0 ]; then
		echo "$name already exists"
		exit 1
#fails to add user to group 
		else
		useradd -m -p $pswrd $name
		[ $? -eq 0 ] && echo "User has been added" || echo "Failed to 			add user"
		fi
	else
		echo "Must have root access to add user"
		exit 2
	fi
	usermod -aG $group $name
done < "$filename"

#deletes user from group
filename="users.txt"
while read -r username password
do
	name="$username"
	pswrd="$password"
	userdel -r $name
	echo "$name has been deleted"
done < "$filename"

if grep -q $group /etc/group
then 
	groupdel $group
else
	echo "Groups does not exist"
fi
