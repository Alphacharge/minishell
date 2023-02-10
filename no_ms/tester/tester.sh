#!/bin/bash

red="\033[1;31m"
green="\033[1;32m"
yell="\033[1;33m"
blue="\033[1;34m"
white="\033[0m"

mini="./mini.out"
bash="./bash.out"
out="./problems"
if [[ -f "$out" ]]; then
	/bin/rm ./problems
fi

i=0;
while read cmd ;do

	./minishell -c "$cmd" > "$mini" 2&>/dev/null
	/bin/bash -c "$cmd" > "$bash" 2&>/dev/null
	same=$(/usr/bin/diff "$mini" "$bash")
	if [[ "$same" != "" ]]; then
		echo -e "$red$cmd$white"
		echo "$cmd" >> $out
	else
		#echo -e "$green" "OK$white"
		echo -e "$green$cmd$white"
	fi
	i=$((i + 1))
done < ./testcases;
#./minishell -c "./src/redirects.sh"

echo "$i Codelines executed."
if [[ -f "$out" ]]; then
	/usr/bin/sort -u $out
	echo "There are Problems. Look into 'problems'."
else
	echo "No Problems found."
fi
/bin/rm $mini $bash