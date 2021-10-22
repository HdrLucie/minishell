# MINISHELL-TESTER

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

# Compile and set executable rights
make -C ../ 
cp ../minishell .
chmod 755 minishell

function exec_test()
{
	echo $@ "; exit" | ./minishell 2>&- 1>sorti
	TEST1=$(tail -n +2 sorti)
	TEST2=$(echo $@ "; exit" | bash 2>&-)
	if [ "$TEST1" != "$TEST2" ]; then
		printf " $BOLDRED%s$RESET" "✗ "
		printf "$CYAN \"$@\" $RESET"
	fi
	# if [ "$TEST1" != "$TEST2" ]; then
	# 	echo
	# 	echo
	# 	printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	# 	printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	# fi
	echo
	sleep 0.1
}

function exec_env()
{
	echo $@ "; exit" | ./minishell 2>&- 1>out_1
	ES_1=$?
	echo $@ "; exit" | bash 2>&- 1>out_2
	ES_2=$?
	sed -i '/SHLVL/d' ./out_1 ./out_2
	sed -i '/declare -x _=/d' ./out_1 ./out_2
	TEST1=$(tail -n +2 out_1)
	TEST2=$(cat out_2)
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
	else
		printf " $BOLDRED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		echo
		echo
		printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
		printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	fi
	echo
	sleep 0.1
}

printf "$BOLDCYAN            ##                ##              ###                ###      ###\n"
printf "                                               ##                 ##       ##\n"
printf " ##  ##    ###     #####     ###      #####    ##       ####      ##       ##\n"
printf " #######    ##     ##  ##     ##     ##        #####   ##  ##     ##       ##\n"
printf " ## # ##    ##     ##  ##     ##      #####    ##  ##  ######     ##       ##\n"
printf " ##   ##    ##     ##  ##     ##          ##   ##  ##  ##         ##       ##\n"
printf " ##   ##   ####    ##  ##    ####    ######   ###  ##   #####    ####     ####\n$RESET"
echo

# exec_test 'echo bonjour ; |'
# exec_test 'echo bonjour | |'
# exec_test '|'
# exec_test 'echo bonjour |;'

exec_test 'echo -n -n -nnnn -nnnnm'
# exec_test 'cat /dev/random | head -n 1 | cat -e'
exec_test 'unset var1 # with undefined var1'

exec_test 'not_cmd bonjour > salut'
# exec_test 'cat Makefile | grep pr | head -n 5 | cd test (mybin) # check status code'
# exec_test 'cat Makefile | grep pr | head -n 5 | cat test (bin) # check status code'
# exec_test 'cat Makefile | grep pr | head -n 5 | hello (NA) # check status code'

exec_test 'cat < test # with non-existent test'

exec_test 'echo bonjour > $test # with test not defined'

# exec_test 'ctrl-\ .131 sur bin'
# exec_test 'echo "bip | bip ; coyotte > < " "'
# exec_test 'cat | cat | cat | ls # check outputs order'
exec_test '$bla # with bla not defined'
# exec_test 'export var ="cat Makefile | grep >"'
exec_test 'c$var Makefile # with var=at'

# exec_test 'sleep 5 | exit'
exec_test 'echo bonjour > $test w/ t'
exec_test 'minishell # binary not in path without "./" before'
exec_test 'cat diufosgid # check exit code'
exec_test 'exit # should return the last exit code value'

# exec_test 'echo coucou | ;'

exec_test 'export ; env'

# exec_test 'echo hudifg d | | hugdfihd'

exec_test 'echo ""'
# exec_test 'echo "\n \n \n"'
exec_test 'echo "\n \n \\n"'
exec_test 'echo hi";" hihi'

exec_test 'cd ~'
exec_test 'cd no_file'
exec_test 'cd a b c d'

# exec_test 'echo |'
# exec_test '| echo'
# exec_test 'sort | ls # check output order'
exec_test 'cat < <'
exec_test 'cat > >'

# exec_test 'cat < Makefile | grep gcc > output'
# exec_test 'exit 0 | exit 1'
# exec_test 'exit 1 | exit 0'

#BOUCLE INFINI
# exec_test '$'

shopt -s extglob 
rm !(*.sh)
