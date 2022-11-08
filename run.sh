msg="ERROR: must receive exactly 1 argument — 'i' or 'r'";

if [[ $# != 1 ]]; then
  echo $msg;
elif [[ $1 == "r" ]]; then
  gcc main.c ABBR/ABBR.c && ./a.out
elif [[ $1 == "i" ]]; then
  gcc main.c ABBI/ABBI.c ABBI/stack.c && ./a.out
else
  echo $msg;
fi
