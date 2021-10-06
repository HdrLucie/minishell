#!/bin/bash

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
make -C ../ > /dev/null
cp ../minishell .
chmod 755 minishell

printf "$BOLDMAGENTA __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
printf "| \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     \n"
printf "| |\/| | | | | . \ | | |  \___ \|  __  |  __| | |    | |     \n"
printf "| |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ \n"
printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$RESET"
echo

printf "$BOLDBLUE         _            _           _           _            _      \n"
printf "        /\ \         /\ \        /\ \        /\ \         /\ \    \n"
printf "       /  \ \       /  \ \      /  \ \      /  \ \       /  \ \   \n"
printf "      / /\ \ \     / /\ \ \    / /\ \ \    / /\ \ \     / /\ \ \  \n"
printf "     / / /\ \_\   / / /\ \_\  / / /\ \_\  / / /\ \ \   / / /\ \_\ \n"
printf "    / /_/_ \/_/  / / /_/ / / / / /_/ / / / / /  \ \_\ / / /_/ / / \n"
printf "   / /____/\    / / /__\/ / / / /__\/ / / / /   / / // / /__\/ /  \n"
printf "  / /\____\/   / / /_____/ / / /_____/ / / /   / / // / /_____/   \n"
printf " / / /______  / / /\ \ \  / / /\ \ \  / / /___/ / // / /\ \ \     \n"
printf "/ / /_______\/ / /  \ \ \/ / /  \ \ \/ / /____\/ // / /  \ \ \    \n"
printf "\/__________/\/_/    \_\/\/_/    \_\/\/_________/ \/_/    \_\/ \n$RESET"
echo

