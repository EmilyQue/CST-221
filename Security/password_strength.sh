#!/bin/bash
#variable for password criteria
x=0

#password is entered and read
echo 'Please enter password: '
read password;

#size variable is set to password
size=${#password}

#checks if password size is less than 8 characters
if (("$size" < 8)); then
	echo 'Password must be at least 8 characters.'
#increments variable
else 
	let "x++"
fi

#checks if password includes numerical characters
if [[ $password =~ [0-9] ]]; then 
#increments variable
	let "x++"

else 
	echo 'Password does not contain any numeric characters'
fi

#checks if password includes any special characters
if [[ $password == *[@#$%'&'*+-=]* ]]; then
#increments variable
	let "x++"
else 
	echo 'Password does not contain any special characters'

fi

#checks if all three criterias are met
if [ "$x" == 3 ]; then
	echo 'Password meets all criteria'
fi
