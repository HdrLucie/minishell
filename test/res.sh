 [1m[31m✗ [0m[36m "cat Makefile" [0m

[1m[31mYour exit status : [1m[31m0[0m
[1m[32mExpected exit status : [1m[32m1[0m

 [1m[31m✗ [0m[36m "" [0m

[1m[31mYour exit status : [1m[31m0[0m
[1m[32mExpected exit status : [1m[32m2[0m

 [1m[32m✓ [0m[36m "echo testtout" [0m
 [1m[32m✓ [0m[36m "echo "coucou"les"amis"" [0m
 [1m[32m✓ [0m[36m "echo testout" [0m
 [1m[32m✓ [0m[36m "echo -n test" [0m
 [1m[31m✗ [0m[36m "echo -n -n -n testtout" [0m

[1m[31mYour output : 
--------------------
[1m[31mtesttout
--------------------[0m
[1m[32mExpected output : 
--------------------
[1m[32mtesttout
--------------------[0m

 [1m[31m✗ [0m[36m "echo "salut"cou""" [0m

[1m[31mYour output : 
--------------------
[1m[31m
--------------------[0m
[1m[32mExpected output : 
--------------------
[1m[32msalutcou
--------------------[0m

 [1m[31m✗ [0m[36m "echo $PATH" [0m

[1m[31mYour output : 
--------------------
[1m[31m/home/elise/.vscode-server/bin/e5a624b788d92b8d34d1392e4c4d9789406efe8f/bin:/home/elise/.vscode-server/bin/e5a624b788d92b8d34d1392e4c4d9789406efe8f/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
> 
--------------------[0m
[1m[32mExpected output : 
--------------------
[1m[32m/home/elise/.vscode-server/bin/e5a624b788d92b8d34d1392e4c4d9789406efe8f/bin:/home/elise/.vscode-server/bin/e5a624b788d92b8d34d1392e4c4d9789406efe8f/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
--------------------[0m

 [1m[31m✗ [0m[36m "cat < ls" [0m

[1m[31mYour exit status : [1m[31m0[0m
[1m[32mExpected exit status : [1m[32m1[0m

 [1m[32m✓ [0m[36m "cat < ls > ls" [0m
 [1m[32m✓ [0m[36m "echo test > ls >> ls >> ls ; echo test >> ls; cat ls" [0m
 [1m[31m✗ [0m[36m "> lol echo test lol; cat lol" [0m

[1m[31mYour output : 
--------------------
[1m[31mtestlol
--------------------[0m
[1m[32mExpected output : 
--------------------
[1m[32mtest lol
--------------------[0m

 [1m[31m✗ [0m[36m ">lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test" [0m

[1m[31mYour output : 
--------------------
[1m[31mmdrtest
--------------------[0m
[1m[32mExpected output : 
--------------------
[1m[32mmdr test
--------------------[0m

 [1m[32m✓ [0m[36m "cat ls > out" [0m
 [1m[32m✓ [0m[36m "cat ls > /dev/null" [0m
 [1m[32m✓ [0m[36m "< /dev/null cat" [0m
